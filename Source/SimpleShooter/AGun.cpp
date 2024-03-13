// Fill out your copyright notice in the Description page of Project Settings.


#include "AGun.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAGun::AAGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AAGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAGun::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("Fire"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector EndVector = Location + Rotation.Vector() * MaxRange;
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Location, EndVector, ECollisionChannel::ECC_GameTraceChannel1))
	{
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 20.f, FColor::Red, true);
	}
}
