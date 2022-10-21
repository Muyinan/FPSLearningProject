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
	FName Name;		// ����
	UPROPERTY(BlueprintReadWrite)
	int Number;			// ����
	UPROPERTY(BlueprintReadWrite)
	bool bCanStacking;	// �Ƿ��ܶѵ�
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Icon;	// ͼ��
	UPROPERTY(BlueprintReadWrite)
	UStaticMesh* Mesh;	// 3Dģ��
	UPROPERTY(BlueprintReadWrite)
	int Tid;			// ��ʱ�ò���
};
