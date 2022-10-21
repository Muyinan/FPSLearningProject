// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "KismetSystemLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < InventorySize; i++) {
		UInventoryItem* emptyItem = NewObject<UInventoryItem>();
		m_ItemList.Add(emptyItem);
	}

	OwnerPawn = Cast<APawn>(this->GetOwner());
	PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItem(UInventoryItem* item)
{
	// 找到物品在背包中的放入位置
	int idx = -1;	
	for (int i = m_ItemList.Num() - 1; i >= 0; i--) {
		if (m_ItemList[i]->Name == "") {
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
		if (m_ItemList[idx]->Name != "") {	// 该格子有物品
			m_ItemList[idx]->Number += item->Number;
		}
		else {
			m_ItemList[idx]->SetProperty(item->Name, item->Number, item->bCanStacking, item->Icon, item->Mesh, item->Tid);
		}
	}

	// 销毁世界中的item
	CurrentFocusItem->Destroy();
}

void UInventoryComponent::RemoveItem(int idx, int num) 
{
	if (num <= 0) return;

	UInventoryItem* ItemRemove = NewObject<UInventoryItem>();
	UInventoryItem* curItem = m_ItemList[idx];
	if (num >= curItem->Number) {
		ItemRemove = curItem;
		m_ItemList[idx] = NewObject<UInventoryItem>();
	}
	else {
		ItemRemove->SetProperty(curItem->Name, num, curItem->bCanStacking, curItem->Icon, curItem->Mesh, curItem->Tid);
		curItem->Number -= num;
	}

	ThrowItem(ItemRemove);
}

void UInventoryComponent::SwapItem(int idx1, int idx2)
{
	Swap(m_ItemList[idx1], m_ItemList[idx2]);
}

void UInventoryComponent::ThrowItem(UInventoryItem* item)
{

}