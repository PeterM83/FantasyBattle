// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpecialRulesLibrary.generated.h"

UENUM(BlueprintType)
enum class ESpecialRule : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Sharpenedhorns UMETA(DisplayName = "Sharpened Horns"),
	E_Unstoppablestampede UMETA(DisplayName = "Unstoppable Stampede"),
	E_Alwaysstrikefirst UMETA(DisplayName = "Always Strike First"),
	E_Alwaysstrikelast UMETA(DisplayName = "Always Strike Last"),
	E_Armorpiercing UMETA(DisplayName = "Armor Piercing"),
	E_Breathweapons UMETA(DisplayName = "Breath Weapons"),
	E_Devastatingcharge UMETA(DisplayName = "Devastating Charge"),
	E_Ethereal UMETA(DisplayName = "Ethereal"),
	E_Extraattck UMETA(DisplayName = "Extra Attack"),
	E_Fastcavalry UMETA(DisplayName = "Fast Cavalry"),
	E_Fear UMETA(DisplayName = "Fear"),
	E_Fightinextraranks UMETA(DisplayName = "Fight in Extra Ranks"),
	E_Flamingattacks UMETA(DisplayName = "Flaming Attacks"),
	E_Flammable UMETA(DisplayName = "Flammable"),
	E_Frenzy UMETA(DisplayName = "Frenzy"),
	E_Fly UMETA(DisplayName = "Fly"),
	E_Hatred UMETA(DisplayName = "Hatred"),
	E_Hover UMETA(DisplayName = "Hover"),
	E_Immunepsychology UMETA(DisplayName = "Immune to Psychology"),
	E_Ignorecover UMETA(DisplayName = "Ignore Cover"),
	E_Impacthits UMETA(DisplayName = "Impact Hits"),
	E_Killingblow UMETA(DisplayName = "Killing Blow"),
	E_Heroickillingblow UMETA(DisplayName = "Heroic Killing Blow"),
	E_Largetarget UMETA(DisplayName = "Large Target"),
	E_Loremaster UMETA(DisplayName = "Loremaster"),
	E_Magicresistance UMETA(DisplayName = "Magic Resistance"),
	E_Monsterandhandlers UMETA(DisplayName = "Monster and Handlers"),
	E_Moveorfire UMETA(DisplayName = "Move or Fire"),
	E_Multipleshots UMETA(DisplayName = "Multiple Shots"),
	E_MultipleWounds UMETA(DisplayName = "Multiple Wounds"),
	E_Poisonedattacks UMETA(DisplayName = "Poisoned Attacks"),
	E_Quicktofire UMETA(DisplayName = "Quick to Fire"),
	E_Randomattacks UMETA(DisplayName = "Random Attacks"),
	E_Randommovement UMETA(DisplayName = "Random Movement"),
	E_Regeneration UMETA(DisplayName = "Regeneration"),
	E_Requirestwohands UMETA(DisplayName = "Requires two Hands"),
	E_Scalyskin UMETA(DisplayName = "Scaly Skin"),
	E_Seacreature UMETA(DisplayName = "Sea Creature"),
	E_Slowtofire UMETA(DisplayName = "Slow to Fire"),
	E_Sniper UMETA(DisplayName = "Sniper"),
	E_Stomp UMETA(DisplayName = "Stomp"),
	E_Strider UMETA(DisplayName = "Strider"),
	E_Stubborn UMETA(DisplayName = "Stubborn"),
	E_Stupidity UMETA(DisplayName = "Stupidity"),
	E_Swiftstride UMETA(DisplayName = "Swiftstride"),
	E_Skirmishers UMETA(DisplayName = "Skirmishers"),
	E_Terror UMETA(DisplayName = "Terror"),
	E_Unbreakable UMETA(DisplayName = "Unbreakable"),
	E_Unstable UMETA(DisplayName = "Unstable"),
	E_Volleyfire UMETA(DisplayName = "Volley Fire"),
	E_Ambushers UMETA(DisplayName = "Ambushers"),
	E_Scouts UMETA(DisplayName = "Scouts"),
	E_Vanguard UMETA(DisplayName = "Vanguard"),
	E_Coldblooded UMETA(DisplayName = "Cold-Blooded"),
	E_Predatoryfighter UMETA(DisplayName = "Predatory Fighter"),
	E_Aquatic UMETA(DisplayName = "Aquatic"),
	E_Spawnkin UMETA(DisplayName = "Spawn-kin"),
	E_Guardians UMETA(DisplayName = "Guardians"),
	E_Sacredduty UMETA(DisplayName = "Sacred Duty"),
	E_Theyareeverywhere UMETA(DisplayName = "They're Everywhere!"),
	E_Chameleon UMETA(DisplayName = "Chameleon"),
	E_Thickskinned UMETA(DisplayName = "Thick-skinned")

};
/**
 * 
 */
UCLASS()
class SPECIALRULES_API USpecialRulesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
