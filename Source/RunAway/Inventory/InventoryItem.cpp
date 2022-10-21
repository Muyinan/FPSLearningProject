// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"

UInventoryItem::UInventoryItem()
{
	// UidΪ0�������Ʒ
	Name = "";
	Number = 0;
	bCanStacking = false;
	Icon = nullptr;
	Mesh = nullptr;
	Tid = 0;
}

void UInventoryItem::SetProperty(FName name, int num, bool stacking, UTexture2D* icon, UStaticMesh* mesh, int id)
{
	Tid = id;
	Number = num;
	bCanStacking = stacking;
	Name = name;
	Icon = icon;
	Mesh = mesh;
}
