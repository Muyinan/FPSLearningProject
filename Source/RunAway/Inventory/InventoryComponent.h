// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNAWAY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	int InventorySize = 30;
	TArray<UInventoryItem*> m_ItemList;
	AActor* CurrentFocusItem;
	APawn* OwnerPawn;
	APlayerController* PlayerController;

private:
	void AddItem(UInventoryItem* item);
	void RemoveItem(int idx, int num);
	void SwapItem(int idx1, int idx2);
	void ThrowItem(UInventoryItem* item);
public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};