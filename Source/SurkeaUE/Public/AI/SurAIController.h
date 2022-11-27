#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SurAIController.generated.h"

class UBehaviorTree;

UCLASS()
class SURKEAUE_API ASurAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
	
};
