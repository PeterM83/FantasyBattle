// Fill out your copyright notice in the Description page of Project Settings.


#include "DiceManager.h"
#include "Components/BoxComponent.h"
#include "Dice.h"

// Sets default values
ADiceManager::ADiceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Stationary);
	RootComponent = Root;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetMobility(EComponentMobility::Stationary);
	FloorMesh->SetupAttachment(RootComponent);

	RoomSize = 250;
	StartDices = 10;

	FloorMesh->SetRelativeScale3D(FVector(RoomSize / 10));

	YPositiveWall = CreateDefaultSubobject<UBoxComponent>(TEXT("YPositiveWall"));
	YPositiveWall->SetBoxExtent(FVector(RoomSize, 10, RoomSize), false);
	YPositiveWall->SetRelativeLocation(FVector(0, RoomSize +5, RoomSize));
	YPositiveWall->SetMobility(EComponentMobility::Stationary);
	YPositiveWall->SetupAttachment(RootComponent);

	YNegativeWall = CreateDefaultSubobject<UBoxComponent>(TEXT("YNegativeWall"));
	YNegativeWall->SetBoxExtent(FVector(RoomSize, 10, RoomSize), false);
	YNegativeWall->SetRelativeLocation(FVector(0, -RoomSize -5, RoomSize));
	ConstructWall(YNegativeWall);

	XPositiveWall = CreateDefaultSubobject<UBoxComponent>(TEXT("XPositiveWall"));
	XPositiveWall->SetBoxExtent(FVector(10, RoomSize, RoomSize), false);
	XPositiveWall->SetRelativeLocation(FVector(RoomSize + 5, 0, RoomSize));
	ConstructWall(XPositiveWall);

	XNegativeWall = CreateDefaultSubobject<UBoxComponent>(TEXT("XNegativeWall"));
	XNegativeWall->SetBoxExtent(FVector(10, RoomSize, RoomSize), false);
	XNegativeWall->SetRelativeLocation(FVector(-RoomSize - 5, 0, RoomSize));
	ConstructWall(XNegativeWall);

}

// Called when the game starts or when spawned
void ADiceManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDice(StartDices);
}

// Called every frame
void ADiceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiceManager::SpawnDice(int32 DiceToSpawn)
{
	UE_LOG(LogActor, Warning, TEXT("Starting to Spawn Dices"));
	for (int32 i = 0; i < DiceToSpawn; ++i)
	{
		FVector SpawnLocation = CreateDieSpawnLocation();
		FRotator SpawnRotation = CreateDieSpawnRotator();
		FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);
		UE_LOG(LogActor, Warning, TEXT("Transform Created"));
		ADice* tempDie = GetWorld()->SpawnActor<ADice>(DieClass, SpawnTransform);
		tempDie->OnRollComplete.AddDynamic(this, &ADiceManager::RecieveRollResult);
		AvailableDice.Add(tempDie);
		tempDie->SetActorHiddenInGame(true);
	}
}

void ADiceManager::ConstructWall(UBoxComponent* Wall)
{
	Wall->SetMobility(EComponentMobility::Stationary);
	Wall->SetupAttachment(RootComponent);
}

void ADiceManager::ResetDieLocation(ADice* Die)
{
}

void ADiceManager::RecieveRollResult(ADice* Die, int32 RollResult, int32 PlayerID)
{
	AvailableDice.Add(Die);

}

FVector ADiceManager::CreateDieSpawnLocation()
{
	FVector SpawnLocation = GetActorLocation();
	int32 tempsize = RoomSize - 35;
	int32 randX = FMath::RandRange(-tempsize, tempsize);
	int32 randY = FMath::RandRange(-tempsize, tempsize);
	int32 randZ = FMath::RandRange(50, RoomSize / 2);
	FVector NewLocation = FVector(randX + SpawnLocation.X, randY + SpawnLocation.Y, randZ + SpawnLocation.Z);
	return NewLocation;
}

FRotator ADiceManager::CreateDieSpawnRotator()
{
	float pitch = FMath::FRandRange(-180.f, 180.f);
	float yaw = FMath::FRandRange(180.f, 180.f);
	float roll = FMath::FRandRange(-180.f, 180.f);
	return FRotator(pitch, yaw, roll);
}

bool ADiceManager::StartRoll1Player(int PlayerID, int Dices)
{
	if (RollOngoing) return false;

	if (Dices > AvailableDice.Num())
	{
		SpawnDice(Dices - AvailableDice.Num());
	}
	for (int i = 0; i < AvailableDice.Num(); i++)
	{
		ADice* Die = AvailableDice[0];
		Die->StartRoll(PlayerID);
		AvailableDice.RemoveAt(0);
	}
	return true;
}


