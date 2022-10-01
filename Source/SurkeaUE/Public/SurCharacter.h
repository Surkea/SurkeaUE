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

	//弹簧臂组件
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	//相机组件
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	// 投射体子类
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	// 界面
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