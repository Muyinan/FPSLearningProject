// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryItem.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
//#include "PickupBase.h"
#include "InventoryHUD.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < InventorySize; i++) {
		AInventoryItem* emptyItem = NewObject<AInventoryItem>();
		m_ItemList.Add(emptyItem);
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(this->GetOwner());
	PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	
	if (BPHUDClass != nullptr)
	{
		BPHUDRef = CreateWidget<UInventoryHUD>(OwnerPawn->GetWorld(), BPHUDClass);
		BPHUDRef->AddToViewport();
		PlayerController->SetInputMode(FInputModeGameOnly());
		BPHUDRef->SetOwningPlayer(PlayerController);
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 射线检测面前是否有pickupBase的子类
	FVector startLoc = OwnerPawn->GetActorLocation();
	FVector lookatVec = UKismetMathLibrary::GetForwardVector(PlayerController->GetControlRotation());
	FVector endLoc = startLoc + TraceLength * lookatVec;
	FHitResult hitRes;
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	//UKismetMathLibrary::LineTraceSingleForObjects(, startLocation, endLocation)
	bool bIsTraced = GetWorld()->LineTraceSingleByObjectType(hitRes,startLoc, endLoc, objectQueryParams);
	if (hitRes.Actor != nullptr){
		CurrentFocusItem = Cast<AInventoryItem>(hitRes.Actor);
	}
	else {
		CurrentFocusItem = nullptr;
	}
	BPHUDRef->CurItem = CurrentFocusItem;
	//// 线段的Debug显示
	//FColor Color = bIsTraced ? FColor::Green : FColor::Red;
	//DrawDebugLine(GetWorld(), startLoc, endLoc, Color, false, 2.0f, 0, 2.0f);
}

void UInventoryComponent::AddItem(AInventoryItem* item)
{
	// 找到物品在背包中的放入位置
	int idx = -1;	
	for (int i = m_ItemList.Num() - 1; i >= 0; i--) {
		if (!m_ItemList[i] || m_ItemList[i]->Name == "") {
			idx = i;
		}
		else {
			if (m_ItemList[i]->Name == item->Name && item->bCanStacking) {
				idx = i;
				break;
			}
		}
	}

	// 开始放入物品
	if (idx == -1) {	// 背包已满
		UE_LOG(LogTemp, Warning, TEXT("Package is full!"));
		return;
	}
	else {
		if (!m_ItemList[idx]) {
			AInventoryItem* emptyItem = NewObject<AInventoryItem>();
			emptyItem->SetProperty(item->Name, item->Number, item->bCanStacking, item->Icon, item->Mesh, item->Tid);
			m_ItemList[idx] = emptyItem;
		}
		else if (m_ItemList[idx]->Name != "") {	// 该格子有物品
			m_ItemList[idx]->Number += item->Number;
		}
		else {
			m_ItemList[idx]->SetProperty(item->Name, item->Number, item->bCanStacking, item->Icon, item->Mesh, item->Tid);
		}
	}

	if (CurrentFocusItem->Name == "TimePause") {
		bPauseGame = true;
	}

	// 销毁世界中的item
	CurrentFocusItem->Destroy();
}

void UInventoryComponent::RemoveItem(int idx, int num)
{
	if (num <= 0) return;

	AInventoryItem* ItemRemove = NewObject<AInventoryItem>();
	for (int i = 0; i < InventorySize; i++) {
		AInventoryItem* curItem = m_ItemList[i];
		if(curItem && curItem->Name != "")
		{
			if (num == 1) {
				if (num >= curItem->Number) {
					ItemRemove = curItem;
					m_ItemList[i] = NewObject<AInventoryItem>();
				}
				else {
					ItemRemove->SetProperty(curItem->Name, num, curItem->bCanStacking, curItem->Icon, curItem->Mesh, curItem->Tid);
					curItem->Number -= num;
				}
			}
			else {
				ItemRemove = curItem;
				m_ItemList[i] = NewObject<AInventoryItem>();
			}
			break;
		}
	}

	if (ItemRemove && ItemRemove->Name == "TimePause") {
		bPauseGame = false;
	}
	ThrowItem(ItemRemove);
}

void UInventoryComponent::SwapItem(int idx1, int idx2)
{
	Swap(m_ItemList[idx1], m_ItemList[idx2]);
}

void UInventoryComponent::ThrowItem(AInventoryItem* item)
{
	FVector pawnPos = OwnerPawn->GetActorLocation();
	FVector pawnForward = OwnerPawn->GetActorForwardVector();
	FVector spawnPos = pawnPos + pawnForward * 100.f;
	FActorSpawnParameters params;
	params.Template = item;
	AInventoryItem* throwItem = GetWorld()->SpawnActor<AInventoryItem>(AInventoryItem::StaticClass(), spawnPos, OwnerPawn->GetActorRotation(), params);
	FVector throwVec = (pawnForward + FVector::UpVector) * ThrowSpeed;
	if(throwItem) throwItem->StaticMeshComp->SetPhysicsLinearVelocity(throwVec, true);
}