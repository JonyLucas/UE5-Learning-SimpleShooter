// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AAGun;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Health", meta=(AllowPrivateAccess="true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category="Shooting", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AAGun> GunClass;

	UPROPERTY()
	AAGun* Gun;
	
	APlayerController* PlayerController;
	void Move(const FInputActionInstance& InputActionInstance);
	void Look(const FInputActionInstance& InputActionInstance);
	void Fire(const FInputActionInstance& InputActionInstance);

};
