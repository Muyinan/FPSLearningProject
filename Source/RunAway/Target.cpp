// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/StaticMeshComponent.h"
#include "TargetSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "RunAwayGameModeBase.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	RootComponent = TargetMesh;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> targetSpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetSpawner::StaticClass(), targetSpawnerArray);
	TargetSpawner = Cast<ATargetSpawner>(targetSpawnerArray[0]);

	GameMode = Cast<ARunAwayGameModeBase>(UGameplayStatics::GetGameMode(this));
	Scale = GameMode->StartScale;
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (this->GetActorScale().X < GameMode->MaxScale) {
		Scale += GameMode->ExpandSpeed * DeltaTime;
		this->SetActorScale3D(FVector(Scale, Scale, Scale));
	}
	else {
		this->ReLoction();
	}
}

void ATarget::ReLoction()
{
	Scale = GameMode->StartScale;
	this->SetActorScale3D(FVector(Scale, Scale, Scale));
	this->SetActorLocation(TargetSpawner->GetSpawnLocation());
}

float ATarget::GetRandomStartScale() 
{
	return 0.0f;
}

