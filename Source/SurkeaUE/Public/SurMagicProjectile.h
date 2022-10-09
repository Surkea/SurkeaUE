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
	// 球体,用于计算碰撞
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	// 投射体，控制球体的运动
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;
	// 粒子系统，控制特效
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
