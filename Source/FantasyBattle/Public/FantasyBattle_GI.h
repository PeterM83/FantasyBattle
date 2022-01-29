// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Templates/SharedPointer.h"
#include "StructLibrary.h"
#include "FantasyBattle_GI.generated.h"

class UUI_LobbyMenu;
class UUI_MainMenu;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSessionCreated, FName, SessionName, bool, bWasSuccessful);

USTRUCT(BlueprintType)
struct FFoundSessionResult
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ConnectInfo;
	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayers;
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPlayers;
	UPROPERTY(BlueprintReadOnly)
	FString HostUserName;
	UPROPERTY(BlueprintReadOnly)
	FString ServerName;

	FOnlineSessionSearchResult SessionData;

	FFoundSessionResult() {}

	FFoundSessionResult(FOnlineSessionSearchResult newSession, FString ConnectString)
	{
		MaxPlayers = newSession.Session.SessionSettings.NumPublicConnections;
		CurrentPlayers = MaxPlayers - newSession.Session.NumOpenPrivateConnections;
		HostUserName = newSession.Session.OwningUserName;
		newSession.Session.SessionSettings.Get("ServerName", ServerName);
		ConnectInfo = ConnectString;
		SessionData = newSession;
	}

};
/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UFantasyBattle_GI : public UGameInstance
{
	GENERATED_BODY()

public:

	UFantasyBattle_GI();

	virtual void Init() override;

	FORCEINLINE bool IsInSession() {return bInSession;}
	
	//~Widgets Start
	UFUNCTION(BlueprintCallable)
	UUI_LobbyMenu* ShowLobbyMenu();
		
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();
		
	UFUNCTION(BlueprintCallable)
	void ShowCreateMenu();
	
	FString FindUserInfo(const FUniqueNetIdRef PlayerID);
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_MainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_LobbyMenu> LobbyMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CreateArmyMenuClass;

	UPROPERTY()
	UUI_MainMenu* MainMenu;

	UPROPERTY()
	UUI_LobbyMenu* LobbyMenu;

	UPROPERTY()
	UUserWidget* CreateMenu;
	
	//~ Widgets End
	//~ OnlineSubsystem Variables/Functions
public:
	UFUNCTION(BlueprintCallable)
	void Login(FString UserName);
	
	UFUNCTION(BlueprintCallable)
	void CreateSession();
	void CreateSession_Server();

	UFUNCTION(BlueprintCallable)
	void DestroySession();
	
	UFUNCTION(BlueprintCallable)
	void GetAllFriends();

	UFUNCTION(BlueprintCallable)
	void ShowFriendsUI();

	UFUNCTION(BlueprintCallable)
	void FindSessions();

	void FindFriendsSessions(const FUniqueNetId& UserID);

	UFUNCTION(BlueprintCallable)
	void JoinSelectedSession(FFoundSessionResult Session);
	
	FOnSessionCreated OnSessionCreated;

protected:

	class IOnlineSubsystem* OnlineSubsystem;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void OnGetFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);
	void OnInvitationAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult);
	void HandleFindSessionsComplete(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search);
	void HandleJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult, FString ConnectInfo);

	UPROPERTY(BlueprintReadWrite)
	bool bInSession;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FFoundSessionResult> Sessions;
	
private:
	
	bool bIsLoggedIn;
	
	FDelegateHandle FindSessionsDelegateHandle;
	FDelegateHandle JoinSessionDelegateHandle;
//~ End OnlineSubsystem
	
	TArray<FUniqueNetIdRef> FriendsIDs;

//~ SaveGame	
	FString SaveGameListString = TEXT("SaveGameList");
	UPROPERTY()
	class UArmySaveGame* SaveGame;
	void InitSaveGameList();

public:
	UFUNCTION(BlueprintCallable)
	bool AddArmyToSave(FArmyStat Army);
	UFUNCTION(BlueprintCallable)	
	bool OverwriteArmy(FArmyStat Army, int32 Index, FString ErrorStr);

	TArray<FArmyStat> GetSaveGameList();
};

