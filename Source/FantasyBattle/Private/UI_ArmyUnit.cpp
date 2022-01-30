// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ArmyUnit.h"
#include "Engine/DataTable.h"

bool UUI_ArmyUnit::Initialize()
{
	bool result = Super::Initialize();
	if (!result)
	{
		return false;
	}

	ID = FGuid::NewGuid();

	return true;
}

void UUI_ArmyUnit::AddProfile_Implementation(const EProfilePrio Prio, const FManProfile Profil)
{
	Profiler.Add(Prio, Profil);
	if (Prio == EProfilePrio::E_Main)
		RecalcUnitValue();
}


void UUI_ArmyUnit::RecalcUnitValue()
{
	float tempValue = (Profiler[EProfilePrio::E_Main].Antal * UnitProfil.ConstructionsValues.Points) + StaticExtraPoints;
	if (Profiler.Contains(EProfilePrio::E_Secondary))
	{
		tempValue += Profiler[EProfilePrio::E_Secondary].Antal * UnitProfil.ConstructionsValues.SecondaryPoints;
	}
	if (tempValue != UnitValue)
	{
		float Diffrence = tempValue - UnitValue;
		UnitValue = tempValue;
		UnitValueChanged(Diffrence, UnitProfil.Rarity);
	}
}

void UUI_ArmyUnit::AddAntal(EProfilePrio Prio, int32 NewAntal)
{
	if (Profiler[Prio].Antal == NewAntal) return;

	Profiler[Prio].Antal = NewAntal;
	UnitAntalChanged(NewAntal, Prio);
	RecalcUnitValue();
}

void UUI_ArmyUnit::AddStaticExtraValue(float AddValue)
{
	StaticExtraPoints += AddValue;

	RecalcUnitValue();
}

void UUI_ArmyUnit::ChangeProfileCost(EProfilePrio Prio, float ExtraValue)
{
	if (Prio == EProfilePrio::E_Main)
	{
		UnitProfil.ConstructionsValues.Points += ExtraValue;
	}
	else if (Prio == EProfilePrio::E_Secondary)
	{
		UnitProfil.ConstructionsValues.SecondaryPoints += ExtraValue;
	}
	RecalcUnitValue();
}

void UUI_ArmyUnit::RemoveProfile(EProfilePrio Prio)
{
	Profiler.Remove(Prio);
}

TMap<EProfilePrio, FManProfile> UUI_ArmyUnit::LoadProfiles(const FMountUpgrade MountUpgrade, UDataTable* ProfilData, EProfilePrio Parent)
{
	TMap<EProfilePrio, FManProfile> tempProfiler;

	FManProfile MountProfile = ProfilData->FindRow<FManProfile>(MountUpgrade.MountName, FString(""));
	if (!MountProfile.ProfileName.IsEmpty())
	{
		MountProfile.Prio = EProfilePrio::E_Mount;
		MountProfile.ParentPrio = EProfilePrio::E_Main;
		tempProfiler.Add(EProfilePrio::E_Mount, MountProfile);
	}

	if (!MountUpgrade.SubUnitName.IsNone())
	{
		FManProfile SubProfile = ProfilData->FindRow<FManProfile>(MountUpgrade.SubUnitName, FString(""));
		if (!SubProfile.ProfileName.IsEmpty())
		{
			SubProfile.Prio = EProfilePrio::E_Sub;
			SubProfile.ParentPrio = EProfilePrio::E_Mount;
			SubProfile.Antal = MountUpgrade.SubUnitCount;
			tempProfiler.Add(EProfilePrio::E_Sub, SubProfile);
		}
	}

	if (!MountUpgrade.SubMountName.IsNone())
	{
		FManProfile SubMountProfile = ProfilData->FindRow<FManProfile>(MountUpgrade.SubMountName, FString(""));
		if (!SubMountProfile.ProfileName.IsEmpty())
		{
			SubMountProfile.Prio = EProfilePrio::E_SubMount;
			SubMountProfile.ParentPrio = EProfilePrio::E_Mount;
			SubMountProfile.Antal = MountUpgrade.SubMountCount;
			tempProfiler.Add(EProfilePrio::E_SubMount, SubMountProfile);
		}
	}

	return tempProfiler;
}
