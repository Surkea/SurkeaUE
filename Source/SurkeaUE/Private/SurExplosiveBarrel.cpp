#include "SurExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASurExplosiveBarrel::ASurExplosiveBarrel()
{
 
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// UE中的“模拟物理”选项
	MeshComp->SetSimulatePhysics(true);
	// 等同于在UE中将“碰撞预设”设置为“PhysicsActor”
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 750.0f;			 // 爆炸范围
	ForceComp->ImpulseStrength = 700.0f; // 冲击力
	ForceComp->bImpulseVelChange = true; // 忽略质量大小；见UE中ForceComp的“冲量速度变更”
}

void ASurExplosiveBarrel::OnActorHit()
{
	ForceComp->FireImpulse();
}
