#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USurInteractionComponent;

UCLASS()
class SURKEAUE_API ASurCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASurCharacter();

protected:

	//���ɱ����
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	//������
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	// Ͷ��������
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	// ����
	UPROPERTY(VisibleAnywhere)
	USurInteractionComponent* InteractionComp;

	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryInteract();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};