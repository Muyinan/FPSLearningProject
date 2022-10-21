// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

class UTexture2D;
class UStaticMesh;

UCLASS(Blueprintable)
class RUNAWAY_API UInventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	UInventoryItem();

	void SetProperty(FName name, int num, bool stacking = true, UTexture2D* icon = nullptr, UStaticMesh* mesh = nullptr, int id = 0);
	
	UPROPERTY(BlueprintReadWrite)
	FName Name;		// 名字
	UPROPERTY(BlueprintReadWrite)
	int Number;			// 数量
	UPROPERTY(BlueprintReadWrite)
	bool bCanStacking;	// 是否能堆叠
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Icon;	// 图标
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Mesh;	// 3D模型
	UPROPERTY(BlueprintReadWrite)
	int Tid;			// 暂时用不上
};
