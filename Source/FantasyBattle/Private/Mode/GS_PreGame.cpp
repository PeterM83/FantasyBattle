// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/GS_PreGame.h"

#include "Mode/PC_FantasyBattle_PreGame.h"
#include "Mode/PS_PreGame.h"
#include "Net/UnrealNetwork.h"

void AGS_PreGame::RunReadyCheck()
{
	if (IsEveryoneReady())
	{
		GameStarting();
		GetWorldTimerManager().SetTimer(GameStartDelay, this, &AGS_PreGame::CountDown, 1.0f, true);
		UE_LOG(LogTemp, Warning, TEXT("Every1 is Ready"));
	}
}

void AGS_PreGame::GameStarting()
{
}

bool AGS_PreGame::IsEveryoneReady()
{
	if (PlayerArray.Num() < 2) return false;

	for (APlayerState* PS : PlayerArray)
	{
		APS_PreGame* LobbyPS = Cast<APS_PreGame>(PS);
		if (LobbyPS)
		{
			if (!LobbyPS->GetIsReady())
				return false;
		}
	}
	return true;
}

void AGS_PreGame::CountDown()
{
}

void AGS_PreGame::OnRep_TimeToGameStartChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("ONREP Time to game start through OnRep before PC Cast"));
	APC_FantasyBattle_PreGame* PC = Cast<APC_FantasyBattle_PreGame>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("ONREP Time to game start through OnRep in Game State: %d"), TimeToGameStart);
		PC->UpdateCountDownTimer(TimeToGameStart);
	}
}

void AGS_PreGame::OnRep_MaxArmySizeChanged()
{
}

void AGS_PreGame::SetMaxArmySize_Implementation(int32 NewMax)
{
	MaxArmySize = NewMax;
}

bool AGS_PreGame::SetMaxArmySize_Validate(int32 NewMax)
{
	return true;
}

void AGS_PreGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGS_PreGame, TimeToGameStart);
	DOREPLIFETIME(AGS_PreGame, MaxArmySize);
}