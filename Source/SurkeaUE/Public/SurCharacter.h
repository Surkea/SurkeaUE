#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};