// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CreationMainMenu.h"
#include "Enumlibrary.h"
#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"
#include "UI_ArmyUnit.h"

bool UUI_CreationMainMenu::Initialize()
{
	bool result = Super::Initialize();
	if (!result)
	{
		return false;
	}
	FString ContextString;

	if (UnitStatTable && BuildUnitClass)
	{
		TArray<FName> UnitNames = UnitStatTable->GetRowNames();
		for (FName Unit : UnitNames)
		{
			FUnitStat TempUnit = UnitStatTable->FindRow<FUnitStat>(Unit, ContextString);

			UUserWidget* tempunit = CreateWidget<UUserWidget>(this, BuildUnitClass);
			//tempunit->Setup(TempUnit, GetRarityColor(TempUnit.Rarity));
			//tempunit->OnClicked.AddDynamic(this, &UUI_CreateMenu::OnBuildUnitButtonClick);
			BuildUnitPanel_Scroll->AddChild(tempunit);
			OnCreationUnitCreated(tempunit, TempUnit, GetRarityColor(TempUnit.Rarity));
		}
	}
	return false;
}

void UUI_CreationMainMenu::CreateArmyUnit(const FUnitStat UnitStats)
{
	if (!ensure(ManStatTable)) return;

	UUI_ArmyUnit* tempunit = CreateWidget<UUI_ArmyUnit>(this, ArmyUnitClass);
	if (tempunit == nullptr) return;

	tempunit->UnitProfil = UnitStats;

	FManProfile MainProfile = ManStatTable->FindRow<FManProfile>(UnitStats.MainProfileName, FString(""));
	MainProfile.Prio = EProfilePrio::E_Main;
	MainProfile.ParentPrio = EProfilePrio::E_Unit;
	MainProfile.Antal = UnitStats.ConstructionsValues.MinAntal;
	tempunit->AddProfile(EProfilePrio::E_Main, MainProfile);

	if (!UnitStats.SecondaryProfileName.IsNone())
	{
		FManProfile secondaryprofile = ManStatTable->FindRow<FManProfile>(UnitStats.SecondaryProfileName, FString(""));
		if (!secondaryprofile.ProfileName.IsEmpty())
		{
			secondaryprofile.Prio = EProfilePrio::E_Secondary;
			secondaryprofile.ParentPrio = EProfilePrio::E_Unit;
			tempunit->AddProfile(EProfilePrio::E_Secondary, secondaryprofile);
		}
	}
	if (!UnitStats.MountProfileName.IsNone())
	{
		FManProfile MountProfile = ManStatTable->FindRow<FManProfile>(UnitStats.MountProfileName, FString(""));
		if (!MountProfile.ProfileName.IsEmpty())
		{
			MountProfile.Prio = EProfilePrio::E_Mount;
			MountProfile.ParentPrio = EProfilePrio::E_Main;
			tempunit->AddProfile(EProfilePrio::E_Mount, MountProfile);
		}
	}
	if (!UnitStats.SubProfileName.IsNone())
	{
		FManProfile SubProfile = ManStatTable->FindRow<FManProfile>(UnitStats.SubProfileName, FString(""));
		if (!SubProfile.ProfileName.IsEmpty())
		{
			SubProfile.Prio = EProfilePrio::E_Sub;
			SubProfile.ParentPrio = EProfilePrio::E_Main;
			SubProfile.Antal = UnitStats.ConstructionsValues.SubProfileCount;
			tempunit->AddProfile(EProfilePrio::E_Sub, SubProfile);
		}
	}
	ArmyIncluded_Scroll->AddChild(tempunit);
	tempunit->ProfilesLoaded();
	OnArmyUnitCreated(tempunit);
}

FLinearColor UUI_CreationMainMenu::GetRarityColor(const EUnitRarity UnitRarity)
{
	switch (UnitRarity)
	{
	case EUnitRarity::E_Lord:
		return RarityColor.LordColor;
	case EUnitRarity::E_Hero:
		return RarityColor.HeroColor;
	case EUnitRarity::E_Core:
		return RarityColor.CoreColor;
	case EUnitRarity::E_Special:
		return RarityColor.SpecialColor;
	case EUnitRarity::E_Rare:
		return RarityColor.RareColor;
	default:
		return FLinearColor::White;
		break;
	}
}


