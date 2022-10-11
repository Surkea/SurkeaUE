#include "SurTargetDummy.h"
#include "SurAttributeComponent.h"

ASurTargetDummy::ASurTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<USurAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASurTargetDummy::OnHealthChanged);
}

void ASurTargetDummy::OnHealthChanged(AActor* InstigatorActor, USurAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// 治愈(>0)或免疫(=0)时不触发受击特效
	if (Delta < 0) {
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

