// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

class UBoxComponent;
class AMainPlayer;
class ATarget;
class UStaticMeshComponent;
class AAmmoTarget;

UCLASS()
class RUNAWAY_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTargetSpawnNumber = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MiniSpawnDistance = 100.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATarget> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATarget> AmmoTarget;

	TArray<ATarget*> Targets;

public:
	FVector GetSpawnLocation();

};
