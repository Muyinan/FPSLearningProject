// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

class UTexture2D;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class RUNAWAY_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name = "";				// 名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Number = 0;					// 数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanStacking = false;		// 是否能堆叠
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon = nullptr;		// 图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh = nullptr;	// 3D模型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Tid = 0;					// 暂时用不上


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComp;		// 外形

	void SetProperty(FName name, int num, bool stacking = true, UTexture2D* icon = nullptr, UStaticMesh* mesh = nullptr, int id = 0);
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
