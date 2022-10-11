#include "SurMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SurAttributeComponent.h"

ASurMagicProjectile::ASurMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASurMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

}

void ASurMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//避免攻击者被自己的粒子伤害
	if (OtherActor && OtherActor != GetInstigator()) {
		//获得AttributeComp
		USurAttributeComponent* AttributeComp = Cast<USurAttributeComponent>(OtherActor->GetComponentByClass(USurAttributeComponent::StaticClass()));
		// 再次判空，可能碰到的是墙壁、箱子等没有血量的物体
		if (AttributeComp) {
			// 魔法粒子造成20血量伤害
			AttributeComp->ApplyHealthChange(-20.0f);
			// 一旦造成伤害就销毁，避免穿过角色继续计算
			Destroy();
		}
	}
}

void ASurMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASurMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}