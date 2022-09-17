// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunAwayGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNAWAY_API ARunAwayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartScale = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExpandSpeed = 0.06f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxScale = 0.2f;

};
