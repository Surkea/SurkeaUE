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

	UFUNCTION()
	void OnActorHit();

};
