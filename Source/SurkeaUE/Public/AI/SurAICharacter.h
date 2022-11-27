#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurAICharacter.generated.h"

UCLASS()
class SURKEAUE_API ASurAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASurAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
