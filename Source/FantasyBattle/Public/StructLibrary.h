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
		int32 MinSecondaryAntal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 SecondaryPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 SubProfileCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 SubMountProfileCount;
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
		float UpgradeCost;

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
		TArray<int32> UpgradeGroup;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 UpgradeGroup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubUnitName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SubUnitCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SubMountName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SubMountCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool MustIncludeSubUpgrade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool CantIncludeSubUpgrade;
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
		SubMountProfileName = NewProfile->SubMountProfileName;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Antal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FManstat ProfileStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		ETroopType TroopType;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FMountUpgrade> MountUpgrade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FSubProfileUpgrade> SubProfileUpgrades;

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
		TroopType = NewProfile->TroopType;
		WizardLvl = NewProfile->WizardLvl;
		WizardLores = NewProfile->WizardLores;
		Weapons = NewProfile->Weapons;
		Armor = NewProfile->Armor;
		SpecialRules = NewProfile->SpecialRules;
		BaseSize = NewProfile->BaseSize;
		SpecialRuleUpgrade = NewProfile->SpecialRuleUpgrade;
		EquipmentUpgrade = NewProfile->EquipmentUpgrade;
		MountUpgrade = NewProfile->MountUpgrade;
		SubProfileUpgrades = NewProfile->SubProfileUpgrades;
		Prio = NewProfile->Prio;
		ParentPrio = NewProfile->ParentPrio;
	}

	bool operator==(const FManProfile& B) const;
};

USTRUCT(BlueprintType)
struct FMountProfile : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText ProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FManstat ProfileStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		ETroopType TroopType;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FSubProfileUpgrade> SubProfileUpgrades;

	FMountProfile()
	{
	}

	FMountProfile(FMountProfile* NewProfile)
	{
		ProfileName = NewProfile->ProfileName;
		ProfileStats = NewProfile->ProfileStats;
		TroopType = NewProfile->TroopType;
		SpecialRules = NewProfile->SpecialRules;
		SubProfile = NewProfile->SubProfile;
		SubMountProfile = NewProfile->SubMountProfile;
		SubCount = NewProfile->SubCount;
		SubMountCount = NewProfile->SubMountCount;
		BaseSize = NewProfile->BaseSize;
		SpecialRuleUpgrade = NewProfile->SpecialRuleUpgrade;
		SubProfileUpgrades = NewProfile->SubProfileUpgrades;

	}

	bool Equals(const FMountProfile& other) const;
	bool operator==(const FMountProfile& other) const;
};

FORCEINLINE bool FMountProfile::Equals(const FMountProfile& other) const
{
	return ProfileName.ToString() == other.ProfileName.ToString();
}

FORCEINLINE bool FMountProfile::operator==(const FMountProfile& other) const
{
	return ProfileName.ToString() == other.ProfileName.ToString();
}

USTRUCT(BlueprintType)
struct FSaveGameUnitProfile : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FUnitStat UnitBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> IncludedUpgrades;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FManProfile> Profiler;

	FSaveGameUnitProfile()
	{

	}

	FSaveGameUnitProfile(FUnitStat Base, TArray<FText> Upgrades, TArray<FManProfile> InProfiles)
	{
		UnitBase = Base;
		IncludedUpgrades = Upgrades;
		Profiler = InProfiles;
	}

};

USTRUCT(BlueprintType)
struct FArmyStat : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ArmyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArmyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ArmyTotalMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EArmies ArmyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSaveGameUnitProfile> Units;

	FArmyStat()
	{
		ArmyValue = 0.f;
		ArmyTotalMax = 2000;
		ArmyType = EArmies::E_Lizardmen;
	}
};

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UStructLibrary : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Profile == Profile", CompactNodeTitle = "==", ScriptMethod = "EqualsManProfile", ScriptOperator = "==", Keywords = "== Equals"), Category = "Math|ManProfile")
		static bool Equals_Profile(const FManProfile& A, const FManProfile& B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Army == Army", CompactNodeTitle = "==", ScriptMethod = "EqualsArmy", ScriptOperator = "==", Keywords = "== Equals"), Category = "Math|Army")
		static bool Equals_Army(const FArmyStat& A, const FArmyStat& B);

};
