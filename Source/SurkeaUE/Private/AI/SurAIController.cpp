// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SurAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASurAIController::BeginPlay() 
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);


	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn) {
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
	}
}