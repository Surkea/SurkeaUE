#include "SurCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurInteractionComponent.h"
#include "SurAttributeComponent.h"
#include "Logging/LogMacros.h"
#include "DrawDebugHelpers.h"


ASurCharacter::ASurCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USurInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USurAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	AttackAnimDelay = 0.2f;
}


void ASurCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 移动控制
	PlayerInputComponent->BindAxis("MoveForward", this, &ASurCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// 跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// 攻击
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASurCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ASurCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("DashAttack", IE_Pressed, this, &ASurCharacter::DashAttack);
	// 交互
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASurCharacter::PrimaryInteract);
}

// 角色向前移动
void ASurCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	// 转向只关注水平Yaw方向，因此置0防止影响
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	// 获取相机（鼠标控制器）的朝向，并朝这个方向移动
	AddMovementInput(ControlRot.Vector(), value);
}

// 角色向右移动
void ASurCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	// 获取相机（鼠标控制器）的朝向，转向右侧，并朝这个方向移动
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

// 左键攻击
void ASurCharacter::PrimaryAttack() {

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASurCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);

}

void ASurCharacter::PrimaryAttack_TimeElapsed() {
	SpawnProjectile(ProjectileClass);
}

// 黑洞攻击
void ASurCharacter::BlackHoleAttack(){
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASurCharacter::BlackHoleAttack_TimeElapsed, AttackAnimDelay);
}
void ASurCharacter::BlackHoleAttack_TimeElapsed() {
	SpawnProjectile(BlackHoleProjectileClass);
}

// 位移攻击
void ASurCharacter::DashAttack() {
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASurCharacter::DashAttack_TimeElapsed, AttackAnimDelay);
}
void ASurCharacter::DashAttack_TimeElapsed() {
	SpawnProjectile(DashProjectileClass);
}

void ASurCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn)) {
		// 获取模型右手位置
		FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");

		// 检测距离为 5000 cm = 50 m
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000);

		// 检测半径
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// 不要检测自己角色
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);


		// 碰撞设置
		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FHitResult Hit;
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3);
		//GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjParams, Params)
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params)) {
			TraceEnd = Hit.ImpactPoint;
			UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *Hit.GetActor()->GetFName().ToString());
			DrawDebugSphere(GetWorld(), TraceEnd, 10.0f, 10, FColor::Yellow, false, 5.0f);
		}


		// 尾向量 - 头向量 = 方向向量 eg: 起点(0,0) 终点(1,1)，方向向量为(1,1)
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - RightHandLoc).Rotator();
		// 朝向检测到的落点方向，在角色的右手位置生成
		FTransform SpawnTM = FTransform(ProjRotation, RightHandLoc);

		UE_LOG(LogTemp, Warning, TEXT("ProjRotation: %s\n"), *ProjRotation.Vector().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("GetControlRotation: %s\n"), *GetControlRotation().Vector().ToString());

		// 此处设置碰撞检测规则为：即使碰撞也总是生成
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		// 生成传入的类
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}

}

// 交互
void ASurCharacter::PrimaryInteract() {

	InteractionComp->PrimaryInteract();
}
