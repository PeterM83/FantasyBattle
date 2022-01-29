// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/LobbyInterface.h"
#include "UI/Lobbby/UI_LobbyMenu.h"
#include "PC_FantasyBattle_PreGame.generated.h"

struct FArmyStat;
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API APC_FantasyBattle_PreGame : public APlayerController, public ILobbyInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(Client, Reliable)
	void C_InitPC();

	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void NewPlayerJoined(const FUniqueNetIdRepl& PlayerID);

	virtual void SetIsReady(bool newValue) override;
	virtual void SetArmy(int32 ArrayIndex) override;
	void UpdateCountDownTimer(int32 TimeLeft);

private:

	UPROPERTY()
	UUI_LobbyMenu* LobbyMenuPtr;

	ILobbyInterface* LobbyInterface;
	
	FTimerHandle WaitingForPlayerStateTimer;
	FTimerHandle LookingForPlayerTimer;
	TArray<FUniqueNetIdRepl> UnfoundPlayers;

	void WaitingForPS();
	void LookingForPlayer();

	TArray<FArmyStat> AvailableArmies;
	FArmyStat SelectedArmy;
};
