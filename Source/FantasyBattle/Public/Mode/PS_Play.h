// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructLibrary.h"
#include "GameFramework/PlayerState.h"
#include "PS_Play.generated.h"

class ABaseUnit;

UCLASS()
class FANTASYBATTLE_API APS_Play : public APlayerState
{
	GENERATED_BODY()

public:
	APS_Play();
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE FArmyStat GetArmy(){return Army;}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetUnitCount() { return OwnGameUnits.Num(); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GotUnits() {return bGotUnits;}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsReadyForDeployment() { return bReadyForDeployment; }
	
	UFUNCTION()
	void SetGameUnitsInternal(const TArray<ABaseUnit*> InGameUnits, uint32 OwningPlayerID);
	void SetArmy(FArmyStat newArmy);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void S_SetIsReadyForDeployment(bool NewValue);
protected:
	
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = ONREP_OwnGameUnits)
	TArray<ABaseUnit*> OwnGameUnits;

	TArray<ABaseUnit*> EnemyGameUnits;

	void SetUnitHighLight(TArray<ABaseUnit*> Units, FLinearColor Color);
private:
	bool bGotUnits;
	
	UPROPERTY(Replicated)
	FArmyStat Army;

	UPROPERTY(Replicated)
	bool bReadyToPlay;

	UPROPERTY(Replicated)
	bool bReadyForDeployment;
		
	UFUNCTION()
	void Onrep_OwnGameUnits();

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
};
