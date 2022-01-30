// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Lobbby/UI_LobbyMenu.h"

#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"

bool UUI_LobbyMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	bIsReady = false;
	
	if (Ready_Btn)
		Ready_Btn->OnClicked.AddDynamic(this, &UUI_LobbyMenu::ReadyClick);

	if (Armies_Combo)
		Armies_Combo->OnSelectionChanged.AddDynamic(this, &UUI_LobbyMenu::ArmySelectionChanged);
	
	return true;
}

void UUI_LobbyMenu::SetupMenu(int32 OwnerID, FString PlayerName)
{
	ParentID = OwnerID;
	CreatePlayerWidget(PlayerName, OwnerID);
}

void UUI_LobbyMenu::SetupArmyInfo(int32 MaxSize, TArray<FArmyStat> Armies)
{
	ArmySize_Text->SetText(FText::FromString(FString::FromInt(MaxSize) + " pts."));
	for (FArmyStat Army : Armies)
	{
		Armies_Combo->AddOption(Army.ArmyName);
	}
	Armies_Combo->SetSelectedIndex(0);
}

void UUI_LobbyMenu::SetLobbyInterface(ILobbyInterface* Interface)
{
	LobbyInterface = Interface;
}

void UUI_LobbyMenu::CountDownToGameStart(int32 TimeLeft)
{
	if (CountDown_Text)
		CountDown_Text->SetText(FText::AsNumber(TimeLeft));
}

void UUI_LobbyMenu::PrepareForGameStart_Implementation()
{
}

void UUI_LobbyMenu::UpdateReadyBtnText()
{
	if (bIsReady)
	{
		ReadyBtn_Text->SetText(FText::FromString("Not Ready"));
		BG_Blur->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		ReadyBtn_Text->SetText(FText::FromString("Ready"));
		BG_Blur->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUI_LobbyMenu::ReadyClick()
{
	bIsReady = !bIsReady;
	UpdateReadyBtnText();
	
	if (LobbyInterface)
		LobbyInterface->SetIsReady(bIsReady);
}

void UUI_LobbyMenu::ArmySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (LobbyInterface)
		LobbyInterface->SetArmy(Armies_Combo->FindOptionIndex(SelectedItem));
}


