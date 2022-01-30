// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GS_Play.h"
#include "StructLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Play.generated.h"

class APlayerController;
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API AGM_Play : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	//Should never be changed, used to test workflow if set to 1 it will start the game after first connection
	UPROPERTY(EditDefaultsOnly)
	int32 NumberOfPlayers = 2;
private:
	FServerPlayerInfo Player1Info;
	FServerPlayerInfo Player2Info;

	FArmyStat DefaultArmy;

	UPROPERTY()
	TArray<APlayerController*> AllPlayers;

};
