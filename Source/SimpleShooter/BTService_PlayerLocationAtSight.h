// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationAtSight.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocationAtSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocationAtSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
