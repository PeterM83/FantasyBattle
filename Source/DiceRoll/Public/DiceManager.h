// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiceManager.generated.h"

UCLASS()
class DICEROLL_API ADiceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ADice> DieClass;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* YPositiveWall;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* YNegativeWall;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* XPositiveWall;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* XNegativeWall;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	TArray<ADice*> AvailableDice;

	void SpawnDice(int32 DiceToSpawn = 1);

	void ConstructWall(UBoxComponent* Wall);

	void ResetDieLocation(ADice* Die);

	UFUNCTION()
	void RecieveRollResult(ADice* Die, int32 RollResult, int32 PlayerID);

	FVector CreateDieSpawnLocation();
	FRotator CreateDieSpawnRotator();

	bool RollOngoing;

protected:

	UPROPERTY(EditDefaultsOnly)
		int32 StartDices;

	UPROPERTY(EditDefaultsOnly)
		int32 RoomSize;

public:

	UFUNCTION(BlueprintCallable)
	bool StartRoll1Player(int PlayerID = 1, int Dices = 1);

};
