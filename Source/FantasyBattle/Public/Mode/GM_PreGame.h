// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_PreGame.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API AGM_PreGame : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGM_PreGame();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	UFUNCTION()
	void SessionCreated(FName SessionName, bool bWasSuccessful);
	void StartGame();
private:


	bool bAllExistingPlayersRegistered;
	FName CurrentSessionName;

	class IOnlineSubsystem* OnlineSubsystem;

	TArray<class APC_FantasyBattle_PreGame*> Players;
};
