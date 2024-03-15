// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationAtSight.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationAtSight::UBTService_PlayerLocationAtSight()
{
	NodeName = TEXT("Update Player Location At Sight");
}

void UBTService_PlayerLocationAtSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()->GetInstigatorController());
	
	if (!PlayerPawn)
	{
		return;
	}

	bool CheckDistance = FVector::Dist(PlayerPawn->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) < 1000.f;

	if(AIController->LineOfSightTo(PlayerPawn) && CheckDistance)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	
}
