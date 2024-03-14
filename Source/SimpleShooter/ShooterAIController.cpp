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
		BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerPawn && LineOfSightTo(PlayerPawn))
	{
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		// 	MoveToActor(PlayerPawn, AcceptanceRadius);
		// 	SetFocus(PlayerPawn);
	}
	else
	{
		BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
		// 	ClearFocus(EAIFocusPriority::Gameplay);
		// 	StopMovement();
	}
}
