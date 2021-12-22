// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpecialRules/Public/SpecialRulesLibrary.h"
#include "EnumLibrary.h"
#include "StructLibrary.generated.h"


USTRUCT(BlueprintType)
struct FUnitConstruction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MinAntal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MaxAntal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Points;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float SecondaryRatio;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 SecondaryPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 SubProfileCount;
};

USTRUCT(BlueprintType)
struct FUnitCommandUpgrade
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 UpgradeCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bChampion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bStandardbearer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bMusician;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FText ChampionName;

	//If it got several profile boosts they are seperated by ;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FText ChampionBonusStat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 ChampionMagicItemLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 StandardMagicItemLimit;
};

USTRUCT(BlueprintType)
struct FManstat
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Weaponskill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Ballisticskill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Toughness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Wound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Initiativ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Leadership;
};

USTRUCT(BlueprintType)
struct FSpecialRule
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		ESpecialRule Rule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EDiceRequirement BonusStat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EDiceNumber DiceStat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 IntStat;

};

USTRUCT(BlueprintType)
struct FBaseUpgrade
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 UpgradeCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText UpgradeText;

};

USTRUCT(BlueprintType)
struct FEquipmentUpgrade : public FBaseUpgrade
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EWeapons> AddWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EWeapons> RemoveWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EArmor> AddArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EArmor> RemoveArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 UpgradeGroup;
};

USTRUCT(BlueprintType)
struct FSpecialRuleUpgrade : public FBaseUpgrade
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<ESpecialRule> AddSpecialRule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<ESpecialRule> RemoveSpecialRule;
};

USTRUCT(BlueprintType)
struct FMountUpgrade : public FBaseUpgrade
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName MountName;
};

USTRUCT(BlueprintType)
struct FSubProfileUpgrade : public FBaseUpgrade
{
	GENERATED_USTRUCT_BODY()

	//Added to the SubProfileCount
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 Antal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EWeapons> AddWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EWeapons> RemoveWeapon;
};

USTRUCT(BlueprintType)
struct FUnitStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText UnitNavn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText UnitPointText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText UnitAntalText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UTexture2D* UnitImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FUnitConstruction ConstructionsValues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EUnitRarity Rarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		ETroopType TroopType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EArmies ArmyGroup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName MainProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SecondaryProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName MountProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubMountProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FUnitCommandUpgrade CommandUpgrades;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FSubProfileUpgrade> SubProfileUpgrades;

	FUnitStat()
	{
		UnitImage = nullptr;
	}

	FUnitStat(FUnitStat* NewProfile)
	{
		UnitNavn = NewProfile->UnitNavn;
		UnitPointText = NewProfile->UnitPointText;
		UnitAntalText = NewProfile->UnitAntalText;
		UnitImage = NewProfile->UnitImage;
		ConstructionsValues = NewProfile->ConstructionsValues;
		Rarity = NewProfile->Rarity;
		TroopType = NewProfile->TroopType;
		ArmyGroup = NewProfile->ArmyGroup;
		MainProfileName = NewProfile->MainProfileName;
		SecondaryProfileName = NewProfile->SecondaryProfileName;
		SubProfileName = NewProfile->SubProfileName;
		MountProfileName = NewProfile->MountProfileName;
		CommandUpgrades = NewProfile->CommandUpgrades;
		SubProfileUpgrades = NewProfile->SubProfileUpgrades;
	}
};

USTRUCT(BlueprintType)
struct FManProfile : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText ProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Antal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FManstat ProfileStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 WizardLvl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<EMagicLores> WizardLores;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<EWeapons> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<EArmor> Armor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ESpecialRule SpecialRules;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FVector BaseSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FSpecialRuleUpgrade> SpecialRuleUpgrade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FEquipmentUpgrade> EquipmentUpgrade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EProfilePrio Prio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EProfilePrio ParentPrio;

	FManProfile()
	{
	}

	FManProfile(FManProfile* NewProfile)
	{
		ProfileName = NewProfile->ProfileName;
		Antal = NewProfile->Antal;
		ProfileStats = NewProfile->ProfileStats;
		WizardLvl = NewProfile->WizardLvl;
		WizardLores = NewProfile->WizardLores;
		Weapons = NewProfile->Weapons;
		Armor = NewProfile->Armor;
		SpecialRules = NewProfile->SpecialRules;
		BaseSize = NewProfile->BaseSize;
		SpecialRuleUpgrade = NewProfile->SpecialRuleUpgrade;
		EquipmentUpgrade = NewProfile->EquipmentUpgrade;
		Prio = NewProfile->Prio;
		ParentPrio = NewProfile->ParentPrio;
	}
};

USTRUCT(BlueprintType)
struct FMountProfile : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText ProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FManstat ProfileStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<ESpecialRule> SpecialRules;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubProfile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubMountProfile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SubCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SubMountCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FVector BaseSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FSpecialRuleUpgrade> SpecialRuleUpgrade;

};
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UStructLibrary : public UObject
{
	GENERATED_BODY()

public:

};
