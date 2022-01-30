// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/GM_Play.h"
#include "FantasyBattle_GI.h"
#include "Mode/PC_Play.h"
#include "Mode/PS_Play.h"

void AGM_Play::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	APC_Play* PC = Cast<APC_Play>(NewPlayer);
	if (PC)
	{
		PC->C_Init();
	}
	AllPlayers.Add(NewPlayer);
	FServerPlayerInfo& PlayerInfo = (AllPlayers.Num() == 1) ? Player1Info : Player2Info;

	PlayerInfo.PC = PC;
	APS_Play* PS = Cast<APS_Play>(NewPlayer->PlayerState);
	UE_LOG(LogTemp, Warning, TEXT("A Player Joined"));
	if (PS)
	{
		if (PS->GetArmy().Units.Num() == 0)
		{
			PS->SetArmy(DefaultArmy);
		}
		PlayerInfo.PS = PS;
		PlayerInfo.SaveGameArmy = PS->GetArmy();
		PlayerInfo.PlayerID = PS->GetPlayerId();
		PlayerInfo.PlayerColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogTemp, Warning, TEXT("PlayerID: %i"), PS->GetPlayerId());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is InValid so we quit"));
		return;
	}
	if (AllPlayers.Num() == NumberOfPlayers)
	{
		AGS_Play* GS = GetGameState<AGS_Play>();
		if (GS)
		{
			GS->InitializeDeploymentPhase(Player1Info, Player2Info);
		}		
	}
}

void AGM_Play::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
	TArray<FArmyStat> armies = GI->GetSaveGameList();
	if (armies.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no default army to load in"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Default Army is loaded"));
	DefaultArmy = armies[0];
}
