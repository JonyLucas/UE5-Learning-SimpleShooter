// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (bIsWinner)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Won!"));
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

		UUserWidget* Widget = CreateWidget(this, WinScreenClass);
		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game has ended! You lost!"));
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

		UUserWidget* Widget = CreateWidget(this, LoseScreenClass);
		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}
	}
}
