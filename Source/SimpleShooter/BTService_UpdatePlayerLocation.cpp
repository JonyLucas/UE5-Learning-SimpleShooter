// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
