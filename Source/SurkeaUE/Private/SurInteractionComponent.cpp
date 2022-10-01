#include "SurInteractionComponent.h"
#include "SurGameplayInterface.h"
#include "DrawDebugHelpers.h"

USurInteractionComponent::USurInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USurInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USurInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USurInteractionComponent::PrimaryInteract()
{
	FHitResult Hit; // �����


	FVector EyeLocation; // ��ɫ�۾�λ��
	FRotator EyeRotation; // ��ɫ���߷���
	AActor* MyOwner = GetOwner(); // ��ȡ���ƽ�ɫ
	// ��������ߵ�λ�úͷ��������EyeLocation��EyeRotation
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	// �������߷���ģ�͵��۾�λ�ÿ�ʼ1000cm����ĵ�Ϊ�յ�
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FCollisionObjectQueryParams ObjectQueryParams; // ��ѯ����
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); // ѡ���ѯ������̬����

	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	// ���жϽ���л�ȡ��⵽��Actor��û��⵽��Ϊ��
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		// �����⵽actor��Ϊ�գ����ж�actor��û��ʵ��SurGameplayInterface��
		if (HitActor->Implements<USurGameplayInterface>()) {
			// ���Ƕ����Interact()����ΪPawn���ͣ����������ת��
			APawn* MyPawn = Cast<APawn>(MyOwner);
			// ��̬�����ݴ����HitActor������Ӧ����
			// ��һ����������Ϊ�գ���������Ѿ��пգ��ڶ��������������Զ���ģ���ʱû��Ӱ�죬���Բ��п�
			ISurGameplayInterface::Execute_Interact(HitActor, MyPawn);
			// ����debug������������ײ�����ߣ���ɫ
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Green, false, 3);
		}
	}
	else { DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 3); }
	
}
