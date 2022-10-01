#include "SurCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurInteractionComponent.h"

ASurCharacter::ASurCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USurInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ASurCharacter::BeginPlay()
{
	Super::BeginPlay();
}
void ASurCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	// 获取模型右手位置
	FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");

	// 朝向角色方向，在角色的右手位置生成
	FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);

	// 此处设置碰撞检测规则为：即使碰撞也总是生成
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// 交互
void ASurCharacter::PrimaryInteract() {

	InteractionComp->PrimaryInteract();
}
