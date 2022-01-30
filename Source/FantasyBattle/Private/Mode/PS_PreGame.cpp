// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/PS_PreGame.h"

#include "Mode/GS_PreGame.h"
#include "Mode/PS_Play.h"
#include "Net/UnrealNetwork.h"

void APS_PreGame::S_SetIsReady_Implementation(bool NewValue)
{
	bIsReady = NewValue;
	if (bIsReady) 
	{
		AGS_PreGame* GS = GetWorld()->GetGameState<AGS_PreGame>();
		if (GS)
		{
			GS->RunReadyCheck();
		}
	}
}

void APS_PreGame::SetArmy(FArmyStat NewArmy)
{
	SelectedArmy = NewArmy;
}

void APS_PreGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APS_PreGame, bIsReady);
	DOREPLIFETIME(APS_PreGame, SelectedArmy);
}

void APS_PreGame::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APS_Play* PS;
	PS = Cast<APS_Play>(PlayerState);
	PS->SetArmy(SelectedArmy);
}
