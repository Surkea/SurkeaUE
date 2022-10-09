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
	// ��������ߡ�Ϊ��ʹ����˫�����ߵĽ�ɫ����ȷ���ã�����ΪPawn������Character
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
