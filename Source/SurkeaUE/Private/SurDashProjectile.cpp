#include "SurDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASurDashProjectile::ASurDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
}

void ASurDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	// ����ըʱ��󣬴���Explode()
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASurDashProjectile::Explode, DetonateDelay);
}

void ASurDashProjectile::Explode_Implementation()
{
	// �����������ϰ�����ǰ��ը����������Ҫ���Timer��ֹ����������
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	// ��ը��Ч
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	// ���ӱ�ը��ر�ϵͳ��ֹͣ�ƶ���ֹͣ��ײ
	EffectComp->DeactivateSystem();
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// ������ʱ��󣬴�������
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASurDashProjectile::TeleportInstigator, TeleportDelay);

	// ������base�е�Explode�е�destroy������Ϊ����ʱ���ʱ����Ҫһ��ʱ��
	//Super::Explode_Implementation();
}

void ASurDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		// ����ʱ���ֽ�ɫԭʼRotation
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
	// ֮ǰû�е��ã���������
	Destroy();
}

