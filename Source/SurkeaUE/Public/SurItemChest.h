#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurGameplayInterface.h"
#include "SurItemChest.generated.h"

UCLASS()
class SURKEAUE_API ASurItemChest : public AActor, public ISurGameplayInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	// UFUNCTION(BlueprintNativeEvent)–ﬁ Œ∫Û±ÿ–ÎÃÌº”_Implementation
	void Interact_Implementation(APawn* InstigatorPawn);

	ASurItemChest();
};
