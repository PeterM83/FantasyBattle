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
	YPositiveWall->SetBoxExtent(FVector(RoomSize, 32, RoomSize), false);
	YPositiveWall->SetRelativeLocation(FVector(0, RoomSize, RoomSize));
	YPositiveWall->SetMobility(EComponentMobility::Stationary);
	YPositiveWall->SetupAttachment(RootComponent);

	YNegativeWall = CreateDefaultSubobject<UBoxComponent>(TEXT("YNegativeWall"));
	YNegativeWall->SetBoxExtent(FVector(-RoomSize, 32, RoomSize), false);
	YNegativeWall->SetRelativeLocation(FVector(0, -RoomSize, RoomSize));
	ConstructWall(YNegativeWall);

	XPositiveWall = CreateDefaultSubobject<UBoxComponent>(TEXT("XPositiveWall"));
	XPositiveWall->SetBoxExtent(FVector(32, RoomSize, RoomSize), false);
	XPositiveWall->SetRelativeLocation(FVector(RoomSize, 0, RoomSize));
	ConstructWall(XPositiveWall);

	XNegativeWall = CreateDefaultSubobject<UBoxComponent>(TEXT("XNegativeWall"));
	XNegativeWall->SetBoxExtent(FVector(32, -RoomSize, RoomSize), false);
	XNegativeWall->SetRelativeLocation(FVector(-RoomSize, 0, RoomSize));
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
	for (int32 i = 0; i < DiceToSpawn; ++i)
	{
		ADice* tempDie = GetWorld()->SpawnActor<ADice>(DieClass, CreateDieSpawnTransform());
		tempDie->OnRollComplete.AddDynamic(this, &ADiceManager::RecieveRollResult);
		AvailableDice.Add(tempDie);
	}
}

void ADiceManager::ConstructWall(UBoxComponent* Wall)
{
	Wall->SetMobility(EComponentMobility::Stationary);
	Wall->SetupAttachment(RootComponent);
}

void ADiceManager::RecieveRollResult(ADice* Die, int32 RollResult, int32 PlayerID)
{
}

FTransform ADiceManager::CreateDieSpawnTransform()
{
	FVector MyLocation = GetActorLocation();
	int32 tempsize = RoomSize - 25;
	int32 randX = FMath::RandRange(-tempsize, tempsize);
	int32 randY = FMath::RandRange(-tempsize, tempsize);
	int32 randZ = FMath::RandRange(50, tempsize);
	FVector SpawnLocation = FVector(randX + MyLocation.X, randY + MyLocation.Y, randZ + MyLocation.Z);
	return FTransform(GetActorRotation(), SpawnLocation, GetActorScale3D());
}

