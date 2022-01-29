// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/GM_PreGame.h"
#include "FantasyBattle_GI.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Mode/GameSession_FantasyBattle.h"
#include "Mode/GS_PreGame.h"
#include "Mode/PC_FantasyBattle_PreGame.h"
#include "Mode/PS_PreGame.h"

AGM_PreGame::AGM_PreGame()
{
	bAllExistingPlayersRegistered = false;
}

void AGM_PreGame::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	OnlineSubsystem = IOnlineSubsystem::Get();

	UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
	if(GI)
	{
		UE_LOG(LogTemp, Warning, TEXT("We found the GI and its valid Casted"));
		GI->OnSessionCreated.BindDynamic(this, &AGM_PreGame::SessionCreated);
	}
	if (IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Warning, TEXT("So we got a dedicated Server running"));
		GI->CreateSession_Server();
		
	}
}

void AGM_PreGame::PostLogin(APlayerController* NewPlayer)
{
	if (!this->bAllExistingPlayersRegistered)
	{
		// RegisterExistingPlayers has not run yet. When it does, it will register this incoming player
		// controller.
		Super::PostLogin(NewPlayer);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Post Login Recieved by Server Session"));
	check(IsValid(NewPlayer));

	// This code handles logins for both the local player (listen server) and remote players (net connection).
	FUniqueNetIdRepl UniqueNetIdRepl;
	if (NewPlayer->IsLocalPlayerController())
	{
		ULocalPlayer *LocalPlayer = NewPlayer->GetLocalPlayer();
		if (IsValid(LocalPlayer))
		{
			UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
		}
		else
		{
			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}
	}
	else
	{
		UNetConnection *RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
		check(IsValid(RemoteNetConnection));
		UniqueNetIdRepl = RemoteNetConnection->PlayerId;
	}
	
	// Get the unique player ID.
	TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
	check(UniqueNetId != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("Post Login Got UniqueNetID and its not NULL"));
	// Get the online session interface.
	IOnlineSubsystem *Subsystem = IOnlineSubsystem::Get();
	IOnlineSessionPtr SessionPtr = Subsystem->GetSessionInterface();
	IOnlineIdentityPtr const IdentityPtr = Subsystem->GetIdentityInterface();
	
	// Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
	if (!SessionPtr->RegisterPlayer(CurrentSessionName, *UniqueNetId, false))
	{
		// The player could not be registered; typically you will want to kick the player from the server in this situation.

	}
	
	Super::PostLogin(NewPlayer);

	for (APC_FantasyBattle_PreGame* Player : Players)
	{
		Player->NewPlayerJoined(UniqueNetId);
	}
	APC_FantasyBattle_PreGame* PC = Cast<APC_FantasyBattle_PreGame>(NewPlayer);
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerID: %d"), PC->PlayerState->GetPlayerId());
		//FString UserName = FindUserInfo(UniqueNetId.ToSharedRef());
		//NewPlayer->PlayerState->SetPlayerName(UserName);
		PC->C_InitPC();
		Players.Add(PC);
	}
}

void AGM_PreGame::SessionCreated(FName SessionName, bool bWasSuccessful)
{
	CurrentSessionName = SessionName;
	UE_LOG(LogTemp, Warning, TEXT("Session Created Called in Pre Game GM"));
	for (auto It = this->GetWorld()->GetPlayerControllerIterator(); It; --It)
	{
		APlayerController* PlayerController = It->Get();
		
		FUniqueNetIdRepl UniqueNetIdRepl;
		if (PlayerController->IsLocalPlayerController())
		{
			ULocalPlayer *LocalPlayer = PlayerController->GetLocalPlayer();
			if (IsValid(LocalPlayer))
			{
				UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
			}
			else
			{
				UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
				check(IsValid(RemoteNetConnection));
				UniqueNetIdRepl = RemoteNetConnection->PlayerId;
			}
		}
		else
		{
			UNetConnection *RemoteNetConnection = Cast<UNetConnection>(PlayerController->Player);
			check(IsValid(RemoteNetConnection));
			UniqueNetIdRepl = RemoteNetConnection->PlayerId;
		}

		// Get the unique player ID.
		TSharedPtr<const FUniqueNetId> UniqueNetId = UniqueNetIdRepl.GetUniqueNetId();
		check(UniqueNetId != nullptr);

		// Get the online session interface.
		IOnlineSubsystem const *Subsystem = IOnlineSubsystem::Get();
		IOnlineSessionPtr const SessionPtr = Subsystem->GetSessionInterface();
		// Register the player with the "MyLocalSessionName" session; this name should match the name you provided in CreateSession.
		if (!SessionPtr->RegisterPlayer(CurrentSessionName, *UniqueNetId, false))
		{
			// The player could not be registered; typically you will want to kick the player from the server in this situation.
		}
	
		/*UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
		if (GI)
		{
			UE_LOG(LogTemp, Warning, TEXT("So we Set the unique Net ID from session to hosting player: %s"), *UniqueNetId->ToString());
			FString UserName = GI->FindUserInfo(UniqueNetId.ToSharedRef());
			UE_LOG(LogTemp, Warning, TEXT("Did we find a username? %s"), *UserName);
			PlayerController->PlayerState->SetUniqueId(UniqueNetId);
			PlayerController->PlayerState->SetPlayerName(UserName);
		}*/
		APC_FantasyBattle_PreGame* PC = Cast<APC_FantasyBattle_PreGame>(PlayerController);
		if (PC)
		{
			PC->C_InitPC();
			Players.Add(PC);
		}
	}
	this->bAllExistingPlayersRegistered = true;
}


