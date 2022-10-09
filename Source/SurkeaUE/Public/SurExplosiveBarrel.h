#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class SURKEAUE_API ASurExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASurExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	virtual void PostInitializeComponents() override;

	// 必须使用UFUNCTION宏才能绑定事件
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
