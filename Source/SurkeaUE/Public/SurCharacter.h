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

	virtual void PostInitializeComponents() override;

	//���ɱ����
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	//������
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	// Ͷ��������
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;
	// ����
	UPROPERTY(VisibleAnywhere)
	USurInteractionComponent* InteractionComp;
	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USurAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USurAttributeComponent* OwningComp, float NewHealth, float Delta);

	//virtual void BeginPlay() override;


	// �ƶ�
	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryInteract();
	// ����
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();
	void DashAttack();
	void DashAttack_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	float AttackAnimDelay;
	// ����
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:

	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};