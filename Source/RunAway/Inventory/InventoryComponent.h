// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AInventoryItem;
class UInventoryHUD;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNAWAY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int InventorySize = 24;
	UPROPERTY(BlueprintReadWrite)
		AInventoryItem* CurrentFocusItem;
	UPROPERTY(BlueprintReadWrite)
		APlayerController* PlayerController;
	UPROPERTY(BlueprintReadWrite)
		APawn* OwnerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryHUD> BPHUDClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ThrowSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPauseGame = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryHUD* BPHUDRef;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AInventoryItem*> m_ItemList;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<AInventoryItem> InventoryItemClass;

	float TraceLength = 1000.f;
protected:
	UFUNCTION(BlueprintCallable)
	void AddItem(AInventoryItem* item);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(int idx, int num);

	UFUNCTION(BlueprintCallable)
	void SwapItem(int idx1, int idx2);

	UFUNCTION(BlueprintCallable)
	void ThrowItem(AInventoryItem* item);
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