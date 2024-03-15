// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "AGun.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Gun = GetWorld()->SpawnActor<AAGun>(GunClass);
	GetMesh()->HideBoneByName("weapon_r", PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerController = Cast<APlayerController>(Controller);

	if(PlayerController)
	{
		if(UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Fire);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}

void AShooterCharacter::Move(const FInputActionInstance& InputActionInstance)
{
	const FVector2d MoveValue = InputActionInstance.GetValue().Get<FVector2d>();
	const FVector MoveDirection = MoveValue.Y * GetActorForwardVector() + MoveValue.X * GetActorRightVector();

	AddMovementInput(MoveDirection.GetSafeNormal2D(), MoveSpeed);
	// AddActorLocalOffset(MoveDirection * MoveSpeed * GetWorld()->DeltaTimeSeconds, true);
}

void AShooterCharacter::Look(const FInputActionInstance& InputActionInstance)
{
	const FVector2d LookValue = InputActionInstance.GetValue().Get<FVector2d>();
	AddControllerPitchInput(-LookValue.Y * RotationRate * GetWorld()->DeltaTimeSeconds);
	AddControllerYawInput(LookValue.X * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::Fire()
{
	Gun->PullTrigger();
}

float AShooterCharacter::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
	if(DamageCauser == this) return 0.f;
	
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageTaken;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	return DamageTaken;
}

