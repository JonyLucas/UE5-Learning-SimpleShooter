// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationAtSight.h"

#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationAtSight::UBTService_PlayerLocationAtSight()
{
	NodeName = TEXT("Update Player Location At Sight");
}

void UBTService_PlayerLocationAtSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()->GetInstigatorController());
	
	if (!PlayerCharacter || !PlayerCharacter->IsAlive())
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}

	// const bool CheckDistance = FVector::Dist(PlayerCharacter->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) < 1000.f;

	if(AIController->LineOfSightTo(PlayerCharacter))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerCharacter->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	
}
