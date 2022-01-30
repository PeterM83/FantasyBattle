// Fill out your copyright notice in the Description page of Project Settings.


#include "Mode/PS_Play.h"

#include "FantasyBattle_GI.h"
#include "Mode/GS_Play.h"
#include "Mode/PC_Play.h"
#include "Net/UnrealNetwork.h"

APS_Play::APS_Play()
{
	bReadyForDeployment = false;
	bReadyToPlay = false;
}

void APS_Play::SetArmy(FArmyStat newArmy)
{
	Army = newArmy;
}

void APS_Play::S_SetIsReadyForDeployment_Implementation(bool NewValue)
{
	if (NewValue != bReadyForDeployment && HasAuthority())
	{
		bReadyForDeployment = NewValue;
		if (NewValue)
		{
			AGS_Play* GS = GetWorld()->GetGameState<AGS_Play>();
			if (GS)
			{
				GS->PlayerReadyForDeployment(GetPlayerId());
				UE_LOG(LogTemp, Warning, TEXT("Player is ready to start Deployment"));
			}
		}
	}
}

bool APS_Play::S_SetIsReadyForDeployment_Validate(bool NewValue)
{
	return true;
}

void APS_Play::SetGameUnitsInternal(const TArray<ABaseUnit*> InGameUnits, uint32 OwningPlayerID)
{
	if (OwningPlayerID == GetPlayerId())
	{
		OwnGameUnits = InGameUnits;
		if (!IsRunningDedicatedServer())
			Onrep_OwnGameUnits();
	}
	else
	{
		EnemyGameUnits = InGameUnits;
	}
}

void APS_Play::Onrep_OwnGameUnits()
{
	for (ABaseUnit* Unit : OwnGameUnits)
	{
		if (Unit == nullptr)
			return;
	}
	APC_Play* PC = Cast<APC_Play>(GetOwner());
	UFantasyBattle_GI* GI = Cast<UFantasyBattle_GI>(GetGameInstance());
	//UE_LOG(LogTemp, Warning, TEXT("OnRep Own Units my Role: %s in playerstate: %i"), *GetEnumText1(Role), this->PlayerId);
	if (!PC)
	{
		SetUnitHighLight(OwnGameUnits, GI->EnemyColor);
		return;
	}

	if (PC->IsLocalPlayerController())
	{
		SetUnitHighLight(OwnGameUnits, GI->OwnColor);
		bGotUnits = true;
		if (PC->GotDeploymentZone())
		{
			S_SetIsReadyForDeployment(true);
		}		
		UE_LOG(LogTemp, Warning, TEXT("GameUnits replicated and there is %d available"), OwnGameUnits.Num());
	}
	else
	{
		SetUnitHighLight(OwnGameUnits, GI->EnemyColor);
	}
}

void APS_Play::SetUnitHighLight(TArray<ABaseUnit*> Units, FLinearColor Color)
{
	
}

void APS_Play::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APS_Play, Army);
	DOREPLIFETIME(APS_Play, bReadyForDeployment);
	DOREPLIFETIME(APS_Play, bReadyToPlay);
	DOREPLIFETIME(APS_Play, OwnGameUnits);
}




