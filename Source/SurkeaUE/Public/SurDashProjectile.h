#pragma once

#include "CoreMinimal.h"
#include "SurProjectileBase.h"
#include "SurDashProjectile.generated.h"


UCLASS()
class SURKEAUE_API ASurDashProjectile : public ASurProjectileBase
{
	GENERATED_BODY()

public:

	ASurDashProjectile();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay; // ´«ËÍÑÓ³Ù

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay; // ±¬Õ¨ÑÓ³Ù

	// hitºóÇå³ý¼ÆÊ±Æ÷
	FTimerHandle TimerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

};
