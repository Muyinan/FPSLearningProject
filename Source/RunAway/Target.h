// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UStaticMeshComponent;
class ARunAwayGameModeBase;
class ATargetSpawner;
class AMainPlayer;
class ATargetSpawner;

UCLASS()
class RUNAWAY_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TargetMesh;

	ATargetSpawner* TargetSpawner;

	void ReLoction();

	float GetRandomStartScale();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scale;

	ARunAwayGameModeBase* GameMode;
};
