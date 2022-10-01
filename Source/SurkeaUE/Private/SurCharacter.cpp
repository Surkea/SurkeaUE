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

	// ��ȡģ������λ��
	FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");

	// �����ɫ�����ڽ�ɫ������λ������
	FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);

	// �˴�������ײ������Ϊ����ʹ��ײҲ��������
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// ����
void ASurCharacter::PrimaryInteract() {

	InteractionComp->PrimaryInteract();
}
