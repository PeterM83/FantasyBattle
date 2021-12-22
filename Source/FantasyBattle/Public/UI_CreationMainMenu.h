// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FantasyBattle/Public/StructLibrary.h"
#include "UI_CreationMainMenu.generated.h"

USTRUCT(BlueprintType)
struct FUnitColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor LordColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor HeroColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor CoreColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor SpecialColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor RareColor;
};
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UUI_CreationMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	////UUI_CreationMainMenu(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		FLinearColor GetRarityColor(const enum EUnitRarity UnitRarity);

		virtual bool Initialize() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
		FUnitColor RarityColor;

	//Called everytime a Buildunit have been created
	UFUNCTION(BlueprintImplementableEvent)
		void OnCreationUnitCreated(UUserWidget* CreationUnit, FUnitStat UnitStats, const FLinearColor UnitColor);

	UFUNCTION(BlueprintCallable)
		void CreateArmyUnit(const FUnitStat UnitStats);

	//Called everytime a ArmyUnit have been created
	UFUNCTION(BlueprintImplementableEvent)
		void OnArmyUnitCreated(class UUI_ArmyUnit* ArmyUnit);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Army", meta = (AllowPrivateAccess = "true"))
		TArray<UUI_ArmyUnit*> IncludedUnits;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
		class UScrollBox* BuildUnitPanel_Scroll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
		UScrollBox* ArmyIncluded_Scroll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		class UDataTable* ManStatTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		UDataTable* UnitStatTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint Class", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> BuildUnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blueprint Class", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUI_ArmyUnit> ArmyUnitClass;

};
