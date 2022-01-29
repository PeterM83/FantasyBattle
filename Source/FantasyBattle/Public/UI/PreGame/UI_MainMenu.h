// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FantasyBattle_GI.h"
#include "Blueprint/UserWidget.h"
#include "UI_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class FANTASYBATTLE_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void FoundSessions(const TArray<FFoundSessionResult>& Sessions);
	
};
