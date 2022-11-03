#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurAttributeComponent.generated.h"

// �����ߣ��ؼ�ӵ���ߣ��ı���Ѫ�����仯ֵ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USurAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURKEAUE_API USurAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

public:	
	USurAttributeComponent();

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float Delta);

};
