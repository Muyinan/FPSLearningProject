// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Target.h"
#include "AmmoTarget.h"
#include "Components/StaticMeshComponent.h"
#include <algorithm>

// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SpawnArea);
}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	// 三个白球
	for (int i = 0; i < MaxTargetSpawnNumber; i++)
	{
		FActorSpawnParameters spawnParameter;
		ATarget* target = GetWorld()->SpawnActor<ATarget>(Target, GetSpawnLocation(), FRotator::ZeroRotator, spawnParameter);
		Targets.Add(target);
	}
	// 一个击中增加弹药的球
	FActorSpawnParameters spawnParameter;
	ATarget* target = GetWorld()->SpawnActor<AAmmoTarget>(AmmoTarget, GetSpawnLocation(), FRotator::ZeroRotator, spawnParameter);
	Targets.Add(target);
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FVector ATargetSpawner::GetSpawnLocation()
{
	float distance;
	FVector spawnPoint;
	do 
	{
		distance = 99999.0f;
		spawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
		for (int i = 0; i < Targets.Num(); i++) {
			distance = std::min(distance, (Targets[i]->GetActorLocation() - spawnPoint).Size());
		}
		if (distance == 99999.0f)
			break;
	} while (distance < MiniSpawnDistance);

	return spawnPoint;
}

