// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GS_Play.generated.h"

class APC_Play;
class APS_Play;
class ABaseUnit;

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	E_PreDeployment UMETA(DisplayName = "Initializing Phase"),
	E_Deployment UMETA(DisplayName = "Deployment"),
	E_Game UMETA(DisplayName = "Game")
};

USTRUCT(BlueprintType)
struct FServerPlayerInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerID;

	UPROPERTY(BlueprintReadOnly)
	APC_Play* PC;

	UPROPERTY(BlueprintReadOnly)
	APS_Play* PS;

	UPROPERTY(BlueprintReadOnly)
	TArray<ABaseUnit*> Units;

	UPROPERTY(BlueprintReadOnly)
	FArmyStat SaveGameArmy;

	UPROPERTY(BlueprintReadOnly)
	FLinearColor PlayerColor;

	FServerPlayerInfo()	{}

	FORCEINLINE bool operator==(const FServerPlayerInfo& other) const
	{
		return (other.PlayerID == PlayerID);
	}

	FORCEINLINE bool operator==(const uint32 otherID) const
	{
		return (otherID == PlayerID);
	}

};

UCLASS()
class FANTASYBATTLE_API AGS_Play : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	void InitializeDeploymentPhase(FServerPlayerInfo& P1, FServerPlayerInfo& P2);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void PlayerReadyForDeployment(uint32 PlayerID);
	
protected:

	virtual void HandleBeginPlay() override;

	void LoadArmy(FServerPlayerInfo& PlayerInfo);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BattleState)
	EBattleState BattleState;
	
private:
	
	UFUNCTION()
	void OnRep_BattleState(EBattleState OldState);
	
	FServerPlayerInfo Player1Info;
	FServerPlayerInfo Player2Info;

	UPROPERTY()
	AActor* DeploymentZone1;

	UPROPERTY()
	AActor* DeploymentZone2;

	UPROPERTY()
	class ADiceManager* DiceManager;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseUnit> UnitClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> DeploymentZoneClass;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
