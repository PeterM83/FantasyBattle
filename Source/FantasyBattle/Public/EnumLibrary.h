// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumLibrary.generated.h"

template<typename TEnum>
static FORCEINLINE FString GetEnumValueToString(const FString& Name, TEnum Value)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}
	return enumPtr->GetDisplayNameTextByValue((int64)Value).ToString();//GetNameByValue((int64)Value).ToString();
}

template<typename T>
static FORCEINLINE TArray<T> EnumGetList(const FString& enumName)
{
	TArray<T> lResult;
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName, true);
	int max = pEnum->ContainsExistingMax() ? pEnum->GetMaxEnumValue() - 1 : pEnum->GetMaxEnumValue();
	for (int i = 0; i <= max; ++i)
	{
		if (pEnum->IsValidEnumValue(i))
			lResult.Add(static_cast<T>(i));
	}
	return lResult;
}


UENUM(BlueprintType)
enum class EArmies : uint8
{
	E_Lizardmen UMETA(DisplayName = "Lizarmen"),
	E_Bretonnia UMETA(DisplayName = "Bretonnia"),
	E_OrcGoblin UMETA(DisplayName = "Orcs and Goblins")
};

UENUM(BlueprintType)
enum class EUnitRarity : uint8
{
	E_Lord UMETA(DisplayName = "Lord"),
	E_Hero UMETA(DisplayName = "Hero"),
	E_Core UMETA(DisplayName = "Core"),
	E_Special UMETA(DisplayName = "Special"),
	E_Rare UMETA(DisplayName = "Rare")
};

UENUM(BlueprintType)
enum class EUpgradeTypes : uint8
{
	E_Command UMETA(DisplayName = "CommandGroup Upgrade"),
	E_Equipment UMETA(DisplayName = "Equipment Upgrade"),
	E_Rule UMETA(DisplayName = "Specialrule Upgrade"),
	E_SubUnit UMETA(DisplayName = "Sub Unit Upgrade"),
	E_Mount UMETA(DisplayName = "Mount Upgrade")
}; 

UENUM(BlueprintType)
enum class ETroopType : uint8
{
	E_Infantry UMETA(DisplayName = "Infantry"),
	E_Monstinf UMETA(DisplayName = "Monstrous Infantry"),
	E_Cavalry UMETA(DisplayName = "Cavalry"),
	E_Monstcavalry UMETA(DisplayName = "Monstrous Cavalry"),
	E_Swarm UMETA(DisplayName = "Swarm"),
	E_Warbeast UMETA(DisplayName = "War Beast"),
	E_Monstbeast UMETA(DisplayName = "Monstrous Beast"),
	E_Monster UMETA(DisplayName = "Monster"),
	E_Chariot UMETA(DisplayName = "Chariot"),
	E_Warmachine UMETA(DisplayName = "War Machine")
};

UENUM(BlueprintType)
enum class EWeapons : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Handweapon UMETA(DisplayName = "Hand Weapon"),
	E_Bow UMETA(DisplayName = "Bow"),
	E_Blowpipe UMETA(DisplayName = "Blowpipe"),
	E_Crossbow UMETA(DisplayName = "Cross Bow"),
	E_Flail UMETA(DisplayName = "Flail"),
	E_Giantblowpipes UMETA(DisplayName = "Giant Blowpipes"),
	E_Giantbow UMETA(DisplayName = "Giant Bow"),
	E_Greatweapon UMETA(DisplayName = "Great Weapon"),
	E_Halberd UMETA(DisplayName = "Halberd"),
	E_Handgun UMETA(DisplayName = "Handgun"),
	E_Lustrianjavelin UMETA(DisplayName = "Lustrian Javelin"),
	E_Javelin UMETA(DisplayName = "Javelin"),
	E_Lance UMETA(DisplayName = "Lance"),
	E_Longbow UMETA(DisplayName = "Longbow"),
	E_Morningstar UMETA(DisplayName = "Morning Star"),
	E_Pistol UMETA(DisplayName = "Pistol"),
	E_Bracepistol_melee UMETA(DisplayName = "Brace of Pistols (Melee)"),
	E_Bracepistol_ranged UMETA(DisplayName = "Brace of Pistols (Ranged)"),
	E_Shortbow UMETA(DisplayName = "Short Bow"),
	E_Sling UMETA(DisplayName = "Sling"),
	E_Spear_foot UMETA(DisplayName = "Spear (Foot)"),
	E_Spear_mount UMETA(DisplayName = "Spear (Mount)"),
	E_Throwingweapon UMETA(DisplayName = "Throwing Weapons"),
	E_Throwingaxes UMETA(DisplayName = "Throwing Axes"),
	E_Additionalhandweapon UMETA(DisplayName = "Additional Hand Weapon"),
	E_Arkofsotek UMETA(DisplayName = "Ark of Sotek"),
	E_Fireleechbolas UMETA(DisplayName = "Fireleech Bolas"),
	E_Solarengine UMETA(DisplayName = "Solar Engine"),
	E_Engineofthegods UMETA(DisplayName = "Engine of the Gods"),
};

UENUM(BlueprintType)
enum class EArmor : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Lightarmor UMETA(DisplayName = "Light Armor"),
	E_Heavyarmor UMETA(DisplayName = "Heavy Armor"),
	E_Shield UMETA(DisplayName = "Shield")
};

UENUM(BlueprintType)
enum class EMagicLores : uint8
{
	E_LoreFire UMETA(DisplayName = "The Lore of Fire"),
	E_LoreBeasts UMETA(DisplayName = "The Lore of Beats"),
	E_LoreMetal UMETA(DisplayName = "The Lore of Metal"),
	E_LoreLight UMETA(DisplayName = "The Lore of Light"),
	E_LoreLife UMETA(DisplayName = "The Lore of Life"),
	E_LoreHeavens UMETA(DisplayName = "The Lore of Heavens"),
	E_LoreShadow UMETA(DisplayName = "The Lore of  Shadow"),
	E_LoreDeath UMETA(DisplayName = "The Lore of Death"),
	E_LoreHighMagic UMETA(DisplayName = "The Lore of High Magic"),
	E_SpellsBigWaaagh UMETA(DisplayName = "Spells of Da Big Waaagh!"),
	E_SpellsLittleWaaagh UMETA(DisplayName = "Spells of Da Little Waaagh!")
};

UENUM(BlueprintType)
enum class EDiceRequirement : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_1p UMETA(DisplayName = "1+"),
	E_2p UMETA(DisplayName = "2+"),
	E_3p UMETA(DisplayName = "3+"),
	E_4p UMETA(DisplayName = "4+"),
	E_5p UMETA(DisplayName = "5+"),
	E_6p UMETA(DisplayName = "6+"),
	E_7p UMETA(DisplayName = "7+")
};

UENUM(BlueprintType)
enum class EDiceNumber : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_D3 UMETA(DisplayName = "D3"),
	E_D6 UMETA(DisplayName = "D6"),
	E_2D6 UMETA(DisplayName = "2D6"),
	E_3D6 UMETA(DisplayName = "3D6")
};

UENUM(BlueprintType)
enum class EProfilePrio : uint8
{
	E_Unit UMETA(DisplayName = "Unit"),
	E_Main UMETA(DisplayName = "Main"),
	E_Secondary UMETA(DisplayName = "Secondary"),
	E_Mount UMETA(DisplayName = "Mount"),
	E_Sub UMETA(DisplayName = "Sub"),
	E_SubMount UMETA(DisplayName = "SubMount")
};
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UEnumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
