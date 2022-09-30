#include "SurCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASurCharacter::ASurCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ASurCharacter::BeginPlay()
{
	Super::BeginPlay();
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

	// ��ȡģ������λ��
	FVector RightHandLoc  = GetMesh()->GetSocketLocation("Muzzle_01");

	// Spawn Transform Matrix�� spawn�ı任����
	// �����ɫ�����ڽ�ɫ������λ������
	FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);

	// �������á�
	// �˴�������ײ������Ϊ����ʹ��ײҲ�������ɣ���Ϊ�����ڽ�ɫ�м����ɱ�Ȼ��ײ
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// �����ܷ��û����ɵĶ�����Actor
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASurCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ��UE�е��õ����ơ���thisָ���ʾ�ƶ������ɫ��&�Զ����ƶ�����
	PlayerInputComponent->BindAxis("MoveForward", this, &ASurCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// �󶨰�������("UE�е��õ�����"��������ʱ���簴�»��ͷţ����󣻾��巽��ʵ��)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASurCharacter::PrimaryAttack);
}