// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (!bIsWinner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game has ended! You lost!"));
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	}
}
