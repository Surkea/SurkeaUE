#include "SurExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASurExplosiveBarrel::ASurExplosiveBarrel()
{
 
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// UE�еġ�ģ������ѡ��
	MeshComp->SetSimulatePhysics(true);
	// ��ͬ����UE�н�����ײԤ�衱����Ϊ��PhysicsActor��
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 750.0f;			 // ��ը��Χ
	ForceComp->ImpulseStrength = 700.0f; // �����
	ForceComp->bImpulseVelChange = true; // ����������С����UE��ForceComp�ġ������ٶȱ����
}

void ASurExplosiveBarrel::OnActorHit()
{
	ForceComp->FireImpulse();
}
