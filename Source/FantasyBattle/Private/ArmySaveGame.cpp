// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmySaveGame.h"
#include "Kismet/GameplayStatics.h"

bool UArmySaveGame::AddArmyToList(FArmyStat Army)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Army to Save in SaveGame"));
	FString ArmyNameCheck = CheckArmyName(Army.ArmyName, Army.ArmyType);
	if (ArmyNameCheck != Army.ArmyName)
		Army.ArmyName = ArmyNameCheck;
	SavedArmies.Add(Army);
	if (!UGameplayStatics::SaveGameToSlot(this, SaveGameList, 0))
	{
		SavedArmies.RemoveAt(SavedArmies.Num() -1);
		UE_LOG(LogTemp, Warning, TEXT("Failed to save %s"), *Army.ArmyName);
		return false;	
	}
	UE_LOG(LogTemp, Warning, TEXT("Successfully saved %s"), *Army.ArmyName);
	return true;
}

bool UArmySaveGame::ReplaceSavedArmy(FArmyStat newArmy, int32 Index, FString& ErrorStr)
{
	UE_LOG(LogTemp, Warning, TEXT("Replacing Army in SaveGame"));
	FString ArmyNameCheck = CheckArmyName(newArmy.ArmyName, newArmy.ArmyType);
	if (ArmyNameCheck != newArmy.ArmyName)
		newArmy.ArmyName = ArmyNameCheck;
	FArmyStat RemovedItem = SavedArmies[Index];
	SavedArmies[Index] = newArmy;
	if (!UGameplayStatics::SaveGameToSlot(this, SaveGameList, 0))
	{
		SavedArmies[Index] = RemovedItem;
		ErrorStr = TEXT("Failed to save %s");
		return false;	
	}
	ErrorStr = TEXT("Successfully saved %s");
	return true;
}

FString UArmySaveGame::CheckArmyName(FString InName, EArmies Race)
{
	bool bFailed = true;
	int32 iteration = 0;
	FString ArmyRaceString = GetEnumValueToString(FString("EArmies"), Race);
	FString ArmyName;
	while (bFailed)
	{
		ArmyName = InName;
		FString TempName = FString("000" + FString::FromInt(iteration));
		if (InName.Equals(FString("")))
		{
			ArmyName = ArmyRaceString + TempName.Right(3);
		}
		else
		{
			if (iteration >= 1)
			{
				ArmyName = ArmyName + TempName.Right(3);
			}
		}
		bFailed = false;
		for (FArmyStat Army : SavedArmies)
		{
			if (ArmyName.Equals(Army.ArmyName))
			{
				bFailed = true;
				break;
			}
		}
		iteration += 1;
	}
	return ArmyName;
}
