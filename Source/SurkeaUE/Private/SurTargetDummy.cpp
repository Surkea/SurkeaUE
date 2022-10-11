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
	// ����(>0)������(=0)ʱ�������ܻ���Ч
	if (Delta < 0) {
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

