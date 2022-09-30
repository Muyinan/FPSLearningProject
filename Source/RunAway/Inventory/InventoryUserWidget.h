// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUserWidget.generated.h"

class UButton;
class UInventoryGrid;

UCLASS()
class RUNAWAY_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryGrid> m_inventoryGridClass;

	UPROPERTY(EditAnywhere)
	int Row = 6;

	UPROPERTY(EditAnywhere)
	int Colum = 6;
};
