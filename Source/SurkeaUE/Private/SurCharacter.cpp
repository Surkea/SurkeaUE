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

	// �ƶ�����
	PlayerInputComponent->BindAxis("MoveForward", this, &ASurCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// ��Ծ
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// ����
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASurCharacter::PrimaryAttack);
	// ����
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASurCharacter::PrimaryInteract);
}

// ��ɫ��ǰ�ƶ�
void ASurCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	// ת��ֻ��עˮƽYaw���������0��ֹӰ��
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	// ��ȡ����������������ĳ��򣬲�����������ƶ�
	AddMovementInput(ControlRot.Vector(), value);
}

// ��ɫ�����ƶ�
void ASurCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0;
	ControlRot.Roll = 0;
	// ��ȡ����������������ĳ���ת���Ҳ࣬������������ƶ�
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

// �������
void ASurCharacter::PrimaryAttack() {

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASurCharacter::PrimaryAttack_TimeElapsed, 0.18f);

}

void ASurCharacter::PrimaryAttack_TimeElapsed() {
	if (ProjectileClass) {
		// ��ȡģ������λ��
		FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");

		// ������Ϊ 5000 cm = 50 m
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + ( GetControlRotation().Vector() * 5000 );

		// ���뾶
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// ��Ҫ����Լ���ɫ
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);


		// ��ײ����
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
		

		// β���� - ͷ���� = �������� eg: ���(0,0) �յ�(1,1)����������Ϊ(1,1)
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - RightHandLoc).Rotator();
		// �����⵽����㷽���ڽ�ɫ������λ������
		FTransform SpawnTM = FTransform(ProjRotation, RightHandLoc);

		UE_LOG(LogTemp, Warning, TEXT("ProjRotation: %s\n"), *ProjRotation.Vector().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("GetControlRotation: %s\n"), *GetControlRotation().Vector().ToString());

		// �˴�������ײ������Ϊ����ʹ��ײҲ��������
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}

// ����
void ASurCharacter::PrimaryInteract() {

	InteractionComp->PrimaryInteract();
}
