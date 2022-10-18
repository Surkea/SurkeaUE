#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;


UCLASS(ABSTRACT)// 'ABSTRACT' marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class SURKEAUE_API ASurProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASurProjectileBase();

protected:
	
	//UPROPERTY(EditDefaultsOnly, Category = "Effects")
	//UParticleSystem* ImpactVFX;//VFX指Visual effects, 即视觉特效

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	// 'virtual' so we can override this in child-classes
	//UFUNCTION()
	//virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assignment, useful for expanding in Blueprint later on
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Explode();

	//virtual void PostInitializeComponents() override;
};
