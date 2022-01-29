// Fill out your copyright notice in the Description page of Project Settings.

#include "Mode/PC_FantasyBattle_PreGame.h"

#include "FantasyBattle_GI.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "GameFramework/PlayerState.h"
#include "Mode/GS_PreGame.h"
#include "Mode/PS_PreGame.h"


void APC_FantasyBattle_PreGame::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);
	
	UE_LOG(LogTemp, Warning, TEXT("Begin Play is running Player Controller"));
	if (IsLocalController())
	{
		UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
		if (GI)
		{
			if (!GI->IsInSession())
			{
				GI->ShowMainMenu();
			}
			AvailableArmies = GI->GetSaveGameList();
		}	
	}
}

void APC_FantasyBattle_PreGame::SetIsReady(bool newValue)
{
	APS_PreGame* PS = Cast<APS_PreGame>(PlayerState);
	if (PS)
	{
		PS->SetIsReady(newValue);
	}
}

void APC_FantasyBattle_PreGame::SetArmy(int32 ArrayIndex)
{
	SelectedArmy = AvailableArmies[ArrayIndex];
}

void APC_FantasyBattle_PreGame::UpdateCountDownTimer(int32 TimeLeft)
{
	
}

void APC_FantasyBattle_PreGame::NewPlayerJoined_Implementation(const FUniqueNetIdRepl& PlayerID)
{
	UnfoundPlayers.Add(PlayerID);
	if (!GetWorldTimerManager().IsTimerActive(LookingForPlayerTimer))
	{
		GetWorldTimerManager().SetTimer(LookingForPlayerTimer, this, &APC_FantasyBattle_PreGame::LookingForPlayer, 0.5f, true);
	}
}

void APC_FantasyBattle_PreGame::WaitingForPS()
{
	if (IsValid(PlayerState) && IsValid(LobbyMenuPtr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found PlayerState and lobby in Waiting for PS"));
		LobbyMenuPtr->SetupMenu(PlayerState->GetPlayerId(), PlayerState->GetPlayerName());
		GetWorldTimerManager().ClearTimer(WaitingForPlayerStateTimer);
		AGS_PreGame* GS = GetWorld()->GetGameState<AGS_PreGame>();
		if (GS)
		{
			for (APlayerState* PS : GS->PlayerArray)
			{
				if (PS->GetPlayerId() != PlayerState->GetPlayerId())
				{
					LobbyMenuPtr->CreatePlayerWidget(PS->GetPlayerName(), PS->GetPlayerId());
				}
			}
		}
	}
}

void APC_FantasyBattle_PreGame::LookingForPlayer()
{
	AGameStateBase* GS = GetWorld()->GetGameState();
	if (GS)
	{
		for (APlayerState* PS : GS->PlayerArray)
		{
			if (UnfoundPlayers.Contains(PS->GetUniqueId()))
			{
				UnfoundPlayers.Remove(PS->GetUniqueId().GetUniqueNetId());
				LobbyMenuPtr->CreatePlayerWidget(PS->GetPlayerName(), PS->GetPlayerId());
			}
		}
	}
	if (UnfoundPlayers.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(LookingForPlayerTimer);
	}
}


void APC_FantasyBattle_PreGame::C_InitPC_Implementation()
{
	if (IsLocalController())
	{
		UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
		if (GI)
		{
			if (GI->IsInSession())
			{
				LobbyMenuPtr = GI->ShowLobbyMenu();
				LobbyMenuPtr->SetLobbyInterface(this);
				AGS_PreGame* GS = Cast<AGS_PreGame>(GetWorld()->GetGameState());
				if (GS)
				{
					LobbyMenuPtr->SetupArmyInfo(GS->GetMaxArmySize(), AvailableArmies);
					
				}
				UE_LOG(LogTemp, Warning, TEXT("PlayerState Cast: %d, LobbyMenu Variabel: %d"), IsValid(PlayerState), IsValid(LobbyMenuPtr));
				if (IsValid(PlayerState) && IsValid(LobbyMenuPtr))
				{
					LobbyMenuPtr->SetupMenu(PlayerState->GetPlayerId(), PlayerState->GetPlayerName());
				}
				else
					GetWorldTimerManager().SetTimer(WaitingForPlayerStateTimer, this, &APC_FantasyBattle_PreGame::WaitingForPS, 0.5f, true);
			}	
		}
	}
}

