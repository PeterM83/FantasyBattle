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
	UFUNCTION(BlueprintNativeEvent)
		void AddProfile(const EProfilePrio Prio, const FManProfile Profil);

	//Called when all Profiles have been loaded
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName ="OnProfilesLoaded"))
		void ProfilesLoaded();

	/*Called when Unitvalue Changes
	@Diffrence is the amount the new value change */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUnitValueChanged"))
		void UnitValueChanged(int32 Diffrence);

	UFUNCTION(BlueprintPure)
		FORCEINLINE FGuid GetID() {return ID;}

	UFUNCTION(BlueprintPure)
		FORCEINLINE GetUnitRarity() {return UnitProfil.Rarity;}

private:

	UPROPERTY(BlueprintReadWrite, Category = "Unit", meta=(AllowPrivateAccess = "true"))
		int32 UnitValue;

	UPROPERTY(BlueprintReadWrite, Category = "Unit", meta = (AllowPrivateAccess = "true"))
		int32 StaticExtraPoints;

		void RecalcUnitValue();

protected:

	UFUNCTION(BlueprintCallable)
		void AddAntal(EProfilePrio Prio, int32 NewAntal);

private:

	UPROPERTY(BlueprintReadWrite, Category = "Identify", meta = (AllowPrivateAccess = "true"))
		FGuid ID;
	
};
