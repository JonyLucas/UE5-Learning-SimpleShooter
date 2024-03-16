// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	const APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
	else
	{
		for(const AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!Controller->IsDead())
			{
				return;
			}
		}

		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
