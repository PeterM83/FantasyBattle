// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnumLibrary.h"
#include "StructLibrary.h"
#include "SpecialRules/Public/SpecialRulesLibrary.h"
#include "UI_ArmyUnit.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UUI_ArmyUnit : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit")
		FUnitStat UnitProfil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
		TMap<EProfilePrio, FManProfile> Profiler;

	//If overriden either add the profile to Profiler or make the call to parent!
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void AddProfile(const EProfilePrio Prio, const FManProfile Profil);

	//Called when all Profiles have been loaded
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName ="OnProfilesLoaded"))
		void ProfilesLoaded();

	//Called when all Profiles have been loaded from a Savegame
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnProfilesLoadedFromSave"))
		void ProfilesLoadedFromSave(const TArray<FText>& IncludedUpgrades);

	/*Called when Unitvalue Changes
	@Diffrence is the amount the new value change */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUnitValueChanged"))
		void UnitValueChanged(float Diffrence, EUnitRarity Rarity);

	/* Called when the number of units change*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUnitAntalChanged"))
		void UnitAntalChanged(int32 NewAntal, EProfilePrio Prio);

	UFUNCTION(BlueprintPure)
		FORCEINLINE FGuid GetID() {return ID;}

	UFUNCTION(BlueprintPure)
		FORCEINLINE EUnitRarity GetUnitRarity() {return UnitProfil.Rarity;}

private:

	UPROPERTY(BlueprintReadOnly, Category = "Unit", meta=(AllowPrivateAccess = "true"))
		float UnitValue;

	UPROPERTY(BlueprintReadOnly, Category = "Unit", meta = (AllowPrivateAccess = "true"))
		float StaticExtraPoints;

		void RecalcUnitValue();

protected:

	UFUNCTION(BlueprintCallable)
		void AddAntal(EProfilePrio Prio, int32 NewAntal);

	UFUNCTION(BlueprintCallable)
		void AddStaticExtraValue(float AddValue);

	UFUNCTION(BlueprintCallable)
		void ChangeProfileCost(EProfilePrio Prio, float ExtraValue);

	UFUNCTION(BlueprintCallable)
		void RemoveProfile(EProfilePrio Prio);

	UFUNCTION(BlueprintCallable)
		TMap<EProfilePrio, FManProfile> LoadProfiles(const FMountUpgrade MountUpgrade, class UDataTable* ProfilData, EProfilePrio Parent);

private:

		FGuid ID;
	
};
