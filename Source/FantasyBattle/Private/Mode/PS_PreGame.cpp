// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/PS_PreGame.h"
#include "Net/UnrealNetwork.h"

void APS_PreGame::SetIsReady(bool NewValue)
{
	bIsReady = NewValue;
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
