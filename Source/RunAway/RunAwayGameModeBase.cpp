// Copyright Epic Games, Inc. All Rights Reserved.


#include "RunAwayGameModeBase.h"

void ARunAwayGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// ��ʾ������Ϣ���롣 
	// -1"��"ֵ������ֹ����Ϣ�����»�ˢ�¡�
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase!"));
	
	UE_LOG(LogTemp, Warning, TEXT("StartScale: %f"), StartScale)
	UE_LOG(LogTemp, Warning, TEXT("ExpandSpeed: %f"), ExpandSpeed)
	UE_LOG(LogTemp, Warning, TEXT("MaxScale: %f"), MaxScale)
}
