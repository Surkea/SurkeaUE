#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURKEAUE_API USurAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

public:	
	USurAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float Delta);

};
