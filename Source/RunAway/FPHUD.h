// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h" 
#include "FPHUD.generated.h"
/**
 * 
 */
UCLASS()
class RUNAWAY_API AFPHUD : public AHUD
{
	GENERATED_BODY()

protected:
    // 准星
    UPROPERTY(EditDefaultsOnly)
    UTexture2D* CrosshairTexture;
public:
    // HUD绘制的主要调用。
    virtual void DrawHUD() override;
};
