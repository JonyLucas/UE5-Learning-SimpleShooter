// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// if (PlayerPawn && LineOfSightTo(PlayerPawn))
	// {
	// 	MoveToActor(PlayerPawn, AcceptanceRadius);
	// 	SetFocus(PlayerPawn);
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}
