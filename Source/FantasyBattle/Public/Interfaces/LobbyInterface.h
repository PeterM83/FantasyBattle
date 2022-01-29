// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructLibrary.h"
#include "UObject/Interface.h"
#include "LobbyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULobbyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FANTASYBATTLE_API ILobbyInterface
{
	GENERATED_BODY()
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void SetArmy(int32 ArrayIndex) = 0;
	
	virtual void SetIsReady(bool newValue) = 0;
public:
};
