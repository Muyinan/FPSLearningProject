// Copyright Epic Games, Inc. All Rights Reserved.


#include "RunAwayGameModeBase.h"

void ARunAwayGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// 显示调试消息五秒。 
	// -1"键"值参数防止该消息被更新或刷新。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase!"));
	
	UE_LOG(LogTemp, Warning, TEXT("StartScale: %f"), StartScale)
	UE_LOG(LogTemp, Warning, TEXT("ExpandSpeed: %f"), ExpandSpeed)
	UE_LOG(LogTemp, Warning, TEXT("MaxScale: %f"), MaxScale)
}
