#include "SurItemChest.h"

ASurItemChest::ASurItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.0f;

}


void ASurItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// ���base������ת������(pitch, yaw, roll)
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

void ASurItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASurItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

