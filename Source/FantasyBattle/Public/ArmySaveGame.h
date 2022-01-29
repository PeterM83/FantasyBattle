// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructLibrary.h"
#include "EnumLibrary.h"
#include "GameFramework/SaveGame.h"
#include "ArmySaveGame.generated.h"


/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UArmySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	bool AddArmyToList(FArmyStat Army);

	bool ReplaceSavedArmy(FArmyStat newArmy, int32 Index, FString& ErrorStr);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetSaveGameString() {return SaveGameList;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FArmyStat> GetSavedArmies() {return SavedArmies;}
	
private:
	
	UPROPERTY(VisibleAnywhere)
	TArray<FArmyStat> SavedArmies;
	
	FString SaveGameList = TEXT("SaveGameList");

	FString CheckArmyName(FString InName, EArmies Race);
};
