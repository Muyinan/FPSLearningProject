// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "AmmoTarget.generated.h"

/**
 * 
 */
UCLASS()
class RUNAWAY_API AAmmoTarget : public ATarget
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AddAmmoNumber = 6;
};
