// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "InventoryGrid.h"
#include "Components/UniformGridSlot.h"

bool UInventoryUserWidget::Initialize()
{
	Super::Initialize();
	
	//Button1->OnClicked.__Internal_AddDynamic(this, &UInventoryUserWidget::OnButton1Click, FName("OnButton1Click"));
	
	//UButton* Button_2 = (UButton*)GetWidgetFromName(TEXT("Button2"));
	//// 添加委托事件
	//FScriptDelegate But2Delegate;
	//But2Delegate.BindUFunction(this, "OnButton2Click");
	//Button_2->OnClicked.Add(But2Delegate);
	UUniformGridPanel* UniGridPanel = (UUniformGridPanel*)GetWidgetFromName(TEXT("UniGridPanel"));
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Colum; j++) {
			UInventoryGrid* inventoryGrid = CreateWidget<UInventoryGrid>(GetWorld(), m_inventoryGridClass);
			UniGridPanel->AddChild(inventoryGrid);
			UUniformGridSlot* gridSlot = Cast<UUniformGridSlot>(inventoryGrid->Slot);
			gridSlot->SetRow(i);
			gridSlot->SetColumn(j);
		}
	}

	return true;
}