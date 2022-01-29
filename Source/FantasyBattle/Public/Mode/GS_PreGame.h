// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GS_PreGame.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API AGS_PreGame : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	void RunReadyCheck();
	
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void SetMaxArmySize(int32 NewMax);

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetMaxArmySize() {return MaxArmySize;}

protected:

	void GameStarting();
	
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing=OnRep_TimeToGameStartChanged)
	uint32 TimeToGameStart = 10;
	
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_MaxArmySizeChanged)
	int32 MaxArmySize = 1500;
	
private:

	bool IsEveryoneReady();

	UFUNCTION()
	void CountDown();
	
	UFUNCTION()
	void OnRep_TimeToGameStartChanged();
	
	UFUNCTION()
	void OnRep_MaxArmySizeChanged();

	FTimerHandle GameStartDelay;

	UPROPERTY()
	class AGameSession_FantasyBattle* CastedSession;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
