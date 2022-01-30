// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/PC_Play.h"

#include "FantasyBattle_GI.h"
#include "Mode/PS_Play.h"

void APC_Play::BeginPlay()
{
	Super::BeginPlay();
}

void APC_Play::C_SetDeploymentZone_Implementation(AActor* Deploymentzone)
{
	if (Deploymentzone == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Deployment zone is invalide"));
	DeploymentZone = Deploymentzone;
	if (GotGameUnits())
		GetPlayerState<APS_Play>()->S_SetIsReadyForDeployment(true);
}

void APC_Play::C_Init_Implementation()
{
	UFantasyBattle_GI* GI = GetGameInstance<UFantasyBattle_GI>();
	if (GI)
	{
		MainUI = GI->ShowPlayMenu();
	}
}


