// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ArmyUnit.h"

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
		int32 Diffrence = tempValue - UnitValue;
		UnitValue = tempValue;
		UnitValueChanged(Diffrence);
	}
}

void UUI_ArmyUnit::AddAntal(EProfilePrio Prio, int32 NewAntal)
{
	if (Profiler[Prio].Antal == NewAntal) return;

	Profiler[Prio].Antal = NewAntal;
	RecalcUnitValue();
}
