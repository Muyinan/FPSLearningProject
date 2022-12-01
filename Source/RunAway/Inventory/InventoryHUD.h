// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHUD.generated.h"

class AInventoryItem;

UCLASS()
class RUNAWAY_API UInventoryHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AInventoryItem* CurItem;
};
