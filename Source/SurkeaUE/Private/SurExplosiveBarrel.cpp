#include "SurExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "SurAttributeComponent.h"

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

// PostInitializeComponents��Actor��ʼ����Ϻ��ٵ���
void ASurExplosiveBarrel::PostInitializeComponents()
{
	// ִ�иú���ԭ���Ĺ���
	Super::PostInitializeComponents();
	// �󶨵�OnComponentHit�¼���
	MeshComp->OnComponentHit.AddDynamic(this, &ASurExplosiveBarrel::OnActorHit);
}

void ASurExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	// log��Ϣ��category��log/warning/error�ȱ�ʾ��־����ϸ�̶ȣ���ӡ����������

	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	// ��ȡ���磬λ�ã���ӡ�����ݣ���Ҫattach��actor����ɫ������ʱ�䣬�Ƿ���Ӱ��
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);

	//USurAttributeComponent* AttributeComp = Cast<USurAttributeComponent>(OtherActor->GetComponentByClass(USurAttributeComponent::StaticClass()));
	//if (AttributeComp) {
	//	UE_LOG(LogTemp, Warning, TEXT("In Attribute!!!!!"));
	//	AttributeComp->ApplyHealthChange(-25.0f);
	}
}
