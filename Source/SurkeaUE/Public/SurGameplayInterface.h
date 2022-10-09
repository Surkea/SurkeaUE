#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurGameplayInterface.generated.h"


UINTERFACE(MinimalAPI)
class USurGameplayInterface : public UInterface
{
	GENERATED_BODY()
};


class SURKEAUE_API ISurGameplayInterface
{
	GENERATED_BODY()

public:
	// 传入调用者。为了使不能双足行走的角色能正确调用，定义为Pawn而不是Character
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
