#include "SurProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASurProjectileBase::ASurProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 500;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

}

//void ASurProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	Explode();
//}

// _Implementation from it being marked as BlueprintNativeEvent
//void ASurProjectileBase::Explode_Implementation()
//{
//	// Check to make sure we aren't already being 'destroyed'
//	// Adding ensure to see if we encounter this situation at all
//	if (ensure(IsPendingKill()))
//	{
//		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
//
//		Destroy();
//	}
//}

//void ASurProjectileBase::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//	//SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
//
//	// More consistent to bind here compared to Constructor which may fail to bind if Blueprint was created before adding this binding (or when using hotreload)
//	// PostInitializeComponent is the preferred way of binding any events.
//	SphereComp->OnComponentHit.AddDynamic(this, &ASurProjectileBase::OnActorHit);
//}

