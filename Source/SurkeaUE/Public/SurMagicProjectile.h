#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class SURKEAUE_API ASurMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASurMagicProjectile();

protected:
	// ����,���ڼ�����ײ
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	// Ͷ���壬����������˶�
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;
	// ����ϵͳ��������Ч
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
