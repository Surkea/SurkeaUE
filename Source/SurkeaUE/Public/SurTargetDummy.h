#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurTargetDummy.generated.h"

class USurAttributeComponent;

UCLASS()
class SURKEAUE_API ASurTargetDummy : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	USurAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USurAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	ASurTargetDummy();
};
