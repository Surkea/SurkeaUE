#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USurInteractionComponent;
class UAnimMontage;
class USurAttributeComponent;

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
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	// 交互
	UPROPERTY(VisibleAnywhere)
	USurInteractionComponent* InteractionComp;
	// 属性
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USurAttributeComponent* AttributeComp;

	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimeElapsed();

	// 动画
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};