#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURKEAUE_API USurInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void PrimaryInteract();

	USurInteractionComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
