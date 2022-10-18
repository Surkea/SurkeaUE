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
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	// 交互
	UPROPERTY(VisibleAnywhere)
	USurInteractionComponent* InteractionComp;
	// 属性
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USurAttributeComponent* AttributeComp;

	//virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	float AttackAnimDelay;

	void PrimaryInteract();
	// 攻击
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	// 动画
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:

	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};