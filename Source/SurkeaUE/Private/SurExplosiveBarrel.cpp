#include "SurExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "SurAttributeComponent.h"

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

// PostInitializeComponents在Actor初始化完毕后再调用
void ASurExplosiveBarrel::PostInitializeComponents()
{
	// 执行该函数原本的功能
	Super::PostInitializeComponents();
	// 绑定到OnComponentHit事件上
	MeshComp->OnComponentHit.AddDynamic(this, &ASurExplosiveBarrel::OnActorHit);
}

void ASurExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	// log信息的category，log/warning/error等表示日志的详细程度，打印的文字内容

	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	// 获取世界，位置，打印的内容，需要attach的actor，颜色，持续时间，是否有影子
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);

	//USurAttributeComponent* AttributeComp = Cast<USurAttributeComponent>(OtherActor->GetComponentByClass(USurAttributeComponent::StaticClass()));
	//if (AttributeComp) {
	//	UE_LOG(LogTemp, Warning, TEXT("In Attribute!!!!!"));
	//	AttributeComp->ApplyHealthChange(-25.0f);
	}
}
