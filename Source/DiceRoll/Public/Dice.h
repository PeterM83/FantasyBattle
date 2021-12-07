// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dice.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRollDone, ADice*, Die, int32, RollResult, int32, PlayerID);

UCLASS()
class DICEROLL_API ADice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADice();

	UFUNCTION(BlueprintCallable)
		void SetDieColor(FLinearColor DieColor, FLinearColor DieDotColor = FLinearColor::Black);

	// ID is used if you got several players rolling at the same time to keep track of who roll
	UFUNCTION(BlueprintCallable)
		void StartRoll(int32 OwnerID = 1);

	UFUNCTION()
	FORCEINLINE bool GetIsRolling() { return bIsRolling; }

	void SetImpulse(float NewImpulse);

	UPROPERTY(BlueprintAssignable)
	FRollDone OnRollComplete;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DieMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerID;

private:

	// Tick event that runs only when the Dice is moving
	void GetRoll();

	class TArray<FVector> FaceNormals;

	float Impulse;

	bool bIsRolling;

	int32 RollResult;

	FTimerHandle RollCheck;

	FBox DiceDimensions;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* DieDotMaterial;

	UPROPERTY(VisibleAnywhere)
		UMaterialInstanceDynamic* DieMaterial;

};
