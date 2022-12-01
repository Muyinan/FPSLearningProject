// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;

	StaticMeshComp->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
	if(Mesh)  StaticMeshComp->SetStaticMesh(Mesh);
}

// Called every frame
void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryItem::SetProperty(FName name, int num, bool stacking, UTexture2D* icon, UStaticMesh* mesh, int id)
{
	Tid = id;
	Number = num;
	bCanStacking = stacking;
	Name = name;
	Icon = icon;
	Mesh = mesh;
}