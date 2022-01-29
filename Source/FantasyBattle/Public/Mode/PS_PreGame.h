// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructLibrary.h"
#include "GameFramework/PlayerState.h"
#include "PS_PreGame.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API APS_PreGame : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetIsReady(bool NewValue);

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsReady() const {return bIsReady;}

	UFUNCTION()
	void SetArmy(FArmyStat NewArmy);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FArmyStat GetArmy() {return SelectedArmy;}
	
private:
	
	UPROPERTY(Replicated)
	bool bIsReady;

	UPROPERTY(Replicated)
	FArmyStat SelectedArmy;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
};
