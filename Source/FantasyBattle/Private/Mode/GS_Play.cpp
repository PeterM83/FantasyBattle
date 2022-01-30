// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/GS_Play.h"
#include "Mode/PC_Play.h"
#include "BaseUnit.h"
#include "DiceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Mode/PS_Play.h"
#include "Net/UnrealNetwork.h"


void AGS_Play::HandleBeginPlay()
{
	Super::HandleBeginPlay();
	if (HasAuthority())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DeploymentZoneClass, FoundActors);
		UE_LOG(LogTemp, Warning, TEXT("Found %d DeploymentZones"), FoundActors.Num());
		if (FoundActors.Num() >= 2)
		{
			DeploymentZone1 = FoundActors[0];
			DeploymentZone2 = FoundActors[1];
		}

		TArray<AActor*> FoundActors2;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADiceManager::StaticClass(), FoundActors2);
		if (FoundActors2.Num() >= 1)
		{
			DiceManager = Cast<ADiceManager>(FoundActors[0]);
			UE_LOG(LogTemp, Warning, TEXT("DiceManager Found"));
		}
	}
}

void AGS_Play::InitializeDeploymentPhase(FServerPlayerInfo& P1, FServerPlayerInfo& P2)
{
	Player1Info = P1;
	Player2Info = P2;

	LoadArmy(Player1Info);
	LoadArmy(Player2Info);

	Player2Info.PC->C_SetDeploymentZone(DeploymentZone1);
	Player1Info.PC->C_SetDeploymentZone(DeploymentZone2);
}

void AGS_Play::LoadArmy(FServerPlayerInfo& PlayerInfo)
{
	if (!ensure(UnitClass)) return;

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	UE_LOG(LogTemp, Warning, TEXT("Starting to Load Army"));
	for (FSaveGameUnitProfile SavedUnit : PlayerInfo.SaveGameArmy.Units)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PlayerInfo.PC;

		ABaseUnit* unit = GetWorld()->SpawnActor<ABaseUnit>(UnitClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (unit)
		{
			unit->InitUnit(SavedUnit, PlayerInfo.PlayerID);
			
			PlayerInfo.Units.Add(unit);
		}
	}
	PlayerInfo.PS->SetGameUnitsInternal(PlayerInfo.Units, PlayerInfo.PlayerID);
	UE_LOG(LogTemp, Warning, TEXT("Done Loading Army"));
}

void AGS_Play::OnRep_BattleState(EBattleState OldState)
{
	UE_LOG(LogTemp, Warning, TEXT("BattleState Replicated Before local test"));
	APC_Play* PC = Cast<APC_Play>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->IsLocalPlayerController())
	{
		// if (BattleState == EBattleState::E_Deployment)
		// {
		// 	PC->StartDeployment();
		// 	UE_LOG(LogTemp, Warning, TEXT("Start Deployment Replicated to Client"));
		// }
		// if (BattleState == EBattleState::E_Game)
		// {
		// 	PC->GameStarted();
		// 	UE_LOG(LogTemp, Warning, TEXT("Start Game Replicated to Client"));
		// }
	}
}

void AGS_Play::PlayerReadyForDeployment_Implementation(uint32 PlayerID)
{
	for (APlayerState* PS : PlayerArray)
	{
		if (PS->GetPlayerId() != PlayerID)
		{
			APS_Play* CastedPS = Cast<APS_Play>(PS);
			if (CastedPS->IsReadyForDeployment())
			{
				BattleState = EBattleState::E_Deployment;
				if (!IsRunningDedicatedServer())
					OnRep_BattleState(EBattleState::E_PreDeployment);
				UE_LOG(LogTemp, Warning, TEXT("GameState got Ready to Deploy for both players"));
			}

		}
	}
}

bool AGS_Play::PlayerReadyForDeployment_Validate(uint32 PlayerID)
{
	return true;
}

void AGS_Play::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGS_Play, BattleState);
}
