// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PS_Play.h"
#include "GameFramework/PlayerController.h"
#include "PC_Play.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API APC_Play : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void C_Init();

	UFUNCTION(Client, Reliable)
	void C_SetDeploymentZone(AActor* Deploymentzone);

	FORCEINLINE bool GotDeploymentZone() { return DeploymentZone == nullptr ? false : true; }

protected:
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GotGameUnits()
	{
		APS_Play* PS = GetPlayerState<APS_Play>();
		if (PS)
			return PS->GotUnits();
		return false;
	}
private:
	UPROPERTY()
	UUserWidget* MainUI;

	UPROPERTY()
	AActor* DeploymentZone;
	
};
