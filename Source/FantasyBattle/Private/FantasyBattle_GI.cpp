// Fill out your copyright notice in the Description page of Project Settings.

#include "FantasyBattle_GI.h"
//#include "..\Public\FantasyBattle_GI.h"
//#include "Interfaces/OnlineSessionInterface.h"
#include "ArmySaveGame.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineExternalUIInterface.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Mode/GM_PreGame.h"
#include "UI/Lobbby/UI_LobbyMenu.h"
#include "UI/PreGame/UI_MainMenu.h"


const FName MySessionName = FName("Test Session");

UFantasyBattle_GI::UFantasyBattle_GI()
{
	bIsLoggedIn = false;
	bInSession = false;

	OwnColor = FLinearColor::Green;
	EnemyColor = FLinearColor::Red;
}

void UFantasyBattle_GI::Init()
{
	Super::Init();

	OnlineSubsystem = IOnlineSubsystem::Get();

	IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
	SessionPtr->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UFantasyBattle_GI::OnInvitationAccepted);

	InitSaveGameList();
	//Login();
	
}

UUI_LobbyMenu* UFantasyBattle_GI::ShowLobbyMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	if (LobbyMenu)
	{
		LobbyMenu->AddToViewport();
		return  LobbyMenu;
	}
	else
	{
		if (!ensureAlways(LobbyMenuClass)) return nullptr;
		LobbyMenu = CreateWidget<UUI_LobbyMenu>(this, LobbyMenuClass);
		if (LobbyMenu)
		{
			//MainMenu->SetMenuInterface(this);
			LobbyMenu->AddToViewport();
			return  LobbyMenu;
		}
	
	}
	return nullptr;
}

UUserWidget* UFantasyBattle_GI::ShowPlayMenu()
{
	if (PlayMenu)
	{
		LobbyMenu->AddToViewport();
		return  PlayMenu;
	}
	else
	{
		if (!ensureAlways(LobbyMenuClass)) return nullptr;
		PlayMenu = CreateWidget<UUserWidget>(this, PlayMenuClass);
		if (PlayMenu)
		{
			//MainMenu->SetMenuInterface(this);
			PlayMenu->AddToViewport();
			return  PlayMenu;
		}
	
	}
	return nullptr;
}

void UFantasyBattle_GI::ShowMainMenu()
{
	if (MainMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("Main Menu added to Viewport"));
		MainMenu->AddToViewport();
	}
	else
	{
		if (!ensureAlways(MainMenuClass)) return;
		MainMenu = CreateWidget<UUI_MainMenu>(this, MainMenuClass);
		if (MainMenu)
		{
			UE_LOG(LogTemp, Warning, TEXT("Main Menu added to Viewport"));
			MainMenu->AddToViewport();
		}
		
	}
}

void UFantasyBattle_GI::ShowCreateMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	if (CreateMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create Menu added to Viewport"));
		CreateMenu->AddToViewport();
	}
	else
	{
		if (!ensureAlways(CreateArmyMenuClass)) return;
		CreateMenu = CreateWidget<UUserWidget>(this, CreateArmyMenuClass);
		if (CreateMenu)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create Menu added to Viewport"));
			CreateMenu->AddToViewport();
		}
		
	}
}

FString UFantasyBattle_GI::FindUserInfo(const FUniqueNetIdRef PlayerID)
{
	IOnlineIdentityPtr IdentityPtr = OnlineSubsystem->GetIdentityInterface();
	FString UserName = IdentityPtr->GetPlayerNickname(PlayerID.Get());
	return UserName;
}

void UFantasyBattle_GI::Login(FString UserName)
{
	if(OnlineSubsystem)
	{
		if(IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			FOnlineAccountCredentials Credentials;
			Credentials.Id = FString("127.0.0.1:6300");
			Credentials.Token = UserName;
			Credentials.Type = FString("developer");
			
			Identity->OnLoginCompleteDelegates->AddUObject(this, &UFantasyBattle_GI::OnLoginComplete);
			Identity->Login(0, Credentials);
		}
	}
}

void UFantasyBattle_GI::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("LoggedIn: %d"), bWasSuccessful);
	bIsLoggedIn = bWasSuccessful;
	
	if (OnlineSubsystem)
	{
		if(IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{			
			Identity->ClearOnLoginCompleteDelegates(0, this);
			TSharedPtr<FUserOnlineAccount> User = Identity->GetUserAccount(UserId);
			UE_LOG(LogTemp, Warning, TEXT("Did we get the right UserName: %s"), *User->GetDisplayName());
			APlayerController* PC = GetFirstLocalPlayerController();
			PC->PlayerState->SetPlayerName(User->GetDisplayName());
		}

	}
}

void UFantasyBattle_GI::CreateSession()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.NumPublicConnections = 3;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = false;
				SessionSettings.Set(FName("ServerName"), FString("FantasyBattleLobby"), EOnlineDataAdvertisementType::ViaOnlineService);
				//SessionSettings.Set(SEARCH_PRESENCE, true, EOnlineDataAdvertisementType::ViaOnlineService);
				
				SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UFantasyBattle_GI::OnCreateSessionComplete);
				SessionPtr->CreateSession(0, MySessionName, SessionSettings);
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CANNOT CREATE SESSION, NOT LOGGED IN"));
	}
}

void UFantasyBattle_GI::CreateSession_Server()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating Session Server called"));
	if (OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating Session Server Subsystem is valid"));
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			UE_LOG(LogTemp, Warning, TEXT("Creating Session Server Found Session interface"));
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsDedicated = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bIsLANMatch = false;
			SessionSettings.NumPublicConnections = 3;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bUsesPresence = false;
			SessionSettings.bUseLobbiesIfAvailable = false;
			SessionSettings.Set(FName("ServerName"), FString("FantasyBattleLobby"), EOnlineDataAdvertisementType::ViaOnlineService);
			//SessionSettings.Set(SEARCH_PRESENCE, true, EOnlineDataAdvertisementType::ViaOnlineService);
				
			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UFantasyBattle_GI::OnCreateSessionComplete);
			SessionPtr->CreateSession(0, MySessionName, SessionSettings);
			UE_LOG(LogTemp, Warning, TEXT("Creating Session Running waiting for callback"));
		}

	}
}

void UFantasyBattle_GI::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Created: %d"), bWasSuccessful);

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
			bInSession = true;
			AGM_PreGame* GM = Cast<AGM_PreGame>(GetWorld()->GetAuthGameMode());
			GM->SessionCreated(SessionName, bWasSuccessful);
			//OnSessionCreated.(SessionName, bWasSuccessful);
			//GetWorld()->ServerTravel("/Game/Maps/Lobby?listen");
			if (EnableListenServer(true))
				UE_LOG(LogTemp, Warning, TEXT("Enabled Listen Server"));
		}

	}
}

void UFantasyBattle_GI::FindSessions()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				TSharedRef<FOnlineSessionSearch> const Search = MakeShared<FOnlineSessionSearch>();
				// Remove the default search parameters that FOnlineSessionSearch sets up.
				Search->QuerySettings.SearchParams.Empty();

				Search->bIsLanQuery = false;
				Search->MaxSearchResults = 200;	
				// Add your search settings here. You must specify at least one filter, or EOS will not run the search.
				Search->QuerySettings.Set(FName("ServerName"), FString("FantasyBattleLobby"), EOnlineComparisonOp::Equals);
				//Search->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
				FindSessionsDelegateHandle = SessionPtr->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsComplete::FDelegate::CreateUObject(this, &UFantasyBattle_GI::HandleFindSessionsComplete, Search));
				
				if (!SessionPtr->FindSessions(0, Search))
				{
					UE_LOG(LogTemp, Warning, TEXT("Search didn't Start"));
				}
			}
		}
	}
}

void UFantasyBattle_GI::FindFriendsSessions(const FUniqueNetId& UserID)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();
				// Remove the default search parameters that FOnlineSessionSearch sets up.
				Search->QuerySettings.SearchParams.Empty();

				Search->bIsLanQuery = false;
				Search->MaxSearchResults = 200;
				// Add your search settings here. You must specify at least one filter, or EOS will not run the search.
				Search->QuerySettings.Set(FName("ServerName"), FString("FantasyBattleLobby"), EOnlineComparisonOp::Equals);
				//Search->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
				FindSessionsDelegateHandle = SessionPtr->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsComplete::FDelegate::CreateUObject(this, &UFantasyBattle_GI::HandleFindSessionsComplete, Search));

				if (!SessionPtr->FindFriendSession(UserID, FriendsIDs))
				{
					UE_LOG(LogTemp, Warning, TEXT("Search didn't Start"));
				}
			}
		}
	}
}

void UFantasyBattle_GI::HandleFindSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
	IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
	FString temp;
	Search->QuerySettings.Get("ServerName", temp);
	UE_LOG(LogTemp, Warning, TEXT("Keyword %s"), *temp);
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("We found %d sessions"), Search->SearchResults.Num());
		for (auto RawResult : Search->SearchResults)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Session owner id: %s. and Name: %s"), *RawResult.Session.OwningUserId->ToString(), *RawResult.Session.OwningUserName);
			if (RawResult.IsValid() || RawResult.IsSessionInfoValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Public: %d - Private: %d"), RawResult.Session.NumOpenPublicConnections, RawResult.Session.NumOpenPrivateConnections);
				UE_LOG(LogTemp, Warning, TEXT("Session Search Result is validated"));
				FString ConnectInfo;
				if (SessionPtr->GetResolvedConnectString(RawResult, NAME_GamePort, ConnectInfo))
				{
					Sessions.Add(FFoundSessionResult(RawResult, ConnectInfo));
					//OnSessionFound.Broadcast(Sessions[Sessions.Num() - 1]);
					//JoinSelectedSession(Sessions[Sessions.Num() - 1]);
					UE_LOG(LogTemp, Warning, TEXT("Server connection info: %s"), *ConnectInfo);
					break;
				}
			}
		}
		if (MainMenu)
		{
			MainMenu->FoundSessions(Sessions);
		}
	}

	SessionPtr->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionsDelegateHandle);
	FindSessionsDelegateHandle.Reset();
}

void UFantasyBattle_GI::JoinSelectedSession(FFoundSessionResult Session)
{
	IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();

	JoinSessionDelegateHandle = SessionPtr->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionComplete::FDelegate::CreateUObject(
			this,
			&UFantasyBattle_GI::HandleJoinSessionComplete,
			Session.ConnectInfo));
	//MainMenu->RemoveFromViewport();
	if (!SessionPtr->JoinSession(0, FName(MySessionName), Session.SessionData))
	{
		UE_LOG(LogTemp, Warning, TEXT("join didn't Start"));
	}
}

void UFantasyBattle_GI::HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult, FString ConnectInfo)
{
	if (JoinResult == EOnJoinSessionCompleteResult::Success ||
		JoinResult == EOnJoinSessionCompleteResult::AlreadyInSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Succeded we just gotta travel there"));
		UE_LOG(LogTemp, Warning, TEXT("open %s"), *ConnectInfo);

		//TravelToSession(ConnectInfo);
		bInSession = true;
		GetWorld()->GetFirstPlayerController()->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Join Failed"));
	}

	IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();

	Session->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
	JoinSessionDelegateHandle.Reset();
}

void UFantasyBattle_GI::DestroySession()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UFantasyBattle_GI::OnDestroySessionComplete);
				SessionPtr->DestroySession(MySessionName);
			}
		}
	}
}

void UFantasyBattle_GI::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				if (SessionPtr->OnDestroySessionCompleteDelegates.IsBound())
					SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
			}
		}
	}
}

void UFantasyBattle_GI::GetAllFriends()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface();

			FriendsPtr->ReadFriendsList(0, FString(""), FOnReadFriendsListComplete::CreateUObject(this, &UFantasyBattle_GI::OnGetFriendsListComplete));
		}
	}
}

void UFantasyBattle_GI::ShowFriendsUI()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			IOnlineExternalUIPtr UIPtr = OnlineSubsystem->GetExternalUIInterface();
			if (UIPtr)
			{
				UIPtr->ShowFriendsUI(0);
				//UIPtr->ShowInviteUI(0, MySessionName);
			}
		}
	}
}

void UFantasyBattle_GI::OnGetFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Read Friends List Succesful"));
		if (OnlineSubsystem)
		{
			if(IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
			{
				TArray<TSharedRef<FOnlineFriend>> FriendsList;
				if (FriendsPtr->GetFriendsList(0, ListName,FriendsList))
				{
					for (TSharedRef<FOnlineFriend> Friend : FriendsList)
					{
						FString FriendName = Friend.Get().GetDisplayName();
						UE_LOG(LogTemp, Warning, TEXT("Friend: %s"), *FriendName);
						FriendsIDs.Add(Friend->GetUserId());
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed getting Friendslist"));
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Read Friends List Failed: %s"), *ErrorStr);
	}
}

void UFantasyBattle_GI::OnInvitationAccepted(const bool bWasSuccessful, const int32 ControllerId,
	FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Invitation Accepted"));
	if (InviteResult.IsValid() || InviteResult.IsSessionInfoValid())
	{
		IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface();
		UE_LOG(LogTemp, Warning, TEXT("Session Search Result is validated"));
		FString ConnectInfo;
		if (SessionPtr->GetResolvedConnectString(InviteResult, NAME_GamePort, ConnectInfo))
		{
			Sessions.Add(FFoundSessionResult(InviteResult, ConnectInfo));
			//OnSessionFound.Broadcast(Sessions[Sessions.Num() - 1]);
			JoinSelectedSession(Sessions[Sessions.Num() - 1]);
			UE_LOG(LogTemp, Warning, TEXT("Server connection info: %s"), *ConnectInfo);
		}
	}
}

void UFantasyBattle_GI::InitSaveGameList()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveGameListString, 0))
	{
		SaveGame = Cast<UArmySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameListString, 0));
		UE_LOG(LogTemp, Warning, TEXT("Loading"));
	}
	else
	{
		SaveGame = Cast<UArmySaveGame>(UGameplayStatics::CreateSaveGameObject(UArmySaveGame::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Creating SaveList"));
	}
}

bool UFantasyBattle_GI::AddArmyToSave(FArmyStat Army)
{
	if (!SaveGame)
	{
		InitSaveGameList();
	}
	return SaveGame->AddArmyToList(Army);
}

bool UFantasyBattle_GI::OverwriteArmy(FArmyStat Army, int32 Index, FString ErrorStr)
{
	if (!SaveGame)
	{
		InitSaveGameList();
	}
	return SaveGame->ReplaceSavedArmy(Army, Index, ErrorStr);
}

TArray<FArmyStat> UFantasyBattle_GI::GetSaveGameList()
{
	if (SaveGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("Allready Exist"));
		return SaveGame->GetSavedArmies();
	}
	InitSaveGameList();
	return SaveGame->GetSavedArmies();
}


