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
	//���⹥���߱��Լ��������˺�
	if (OtherActor && OtherActor != GetInstigator()) {
		//���AttributeComp
		USurAttributeComponent* AttributeComp = Cast<USurAttributeComponent>(OtherActor->GetComponentByClass(USurAttributeComponent::StaticClass()));
		// �ٴ��пգ�������������ǽ�ڡ����ӵ�û��Ѫ��������
		if (AttributeComp) {
			// ħ���������20Ѫ���˺�
			AttributeComp->ApplyHealthChange(-20.0f);
			// һ������˺������٣����⴩����ɫ��������
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