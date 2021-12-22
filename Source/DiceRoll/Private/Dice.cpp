// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"

// Sets default values
ADice::ADice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DieMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DieMesh"));
	RootComponent = DieMesh;

	FaceNormals.Add(FVector(0, 1, 0));
	FaceNormals.Add(FVector(0, 0, -1));
	FaceNormals.Add(FVector(1, 0, 0));
	FaceNormals.Add(FVector(-1, 0, 0));
	FaceNormals.Add(FVector(0, 0, 1));
	FaceNormals.Add(FVector(0, -1, 0));

	DieMesh->SetSimulatePhysics(true);

	DieMesh->SetMobility(EComponentMobility::Movable);

	Impulse = 5000;

	DiceDimensions = FBox(FVector(-10, -10, -10), FVector(10, 10, 10));
}

void ADice::SetDieColor(FLinearColor DieColor, FLinearColor DieDotColor)
{
	if (DieMaterial)
	{
		DieMaterial->SetVectorParameterValue("Color", DieColor);
	}
	if (DieDotMaterial)
	{
		DieDotMaterial->SetVectorParameterValue("Color", DieDotColor);
	}
}

void ADice::StartRoll(int32 OwnerID)
{
	if (!bIsRolling)
	{
		if (GetWorldTimerManager().IsTimerActive(HideTimer))
		{
			GetWorldTimerManager().ClearTimer(HideTimer);
		}
		SetActorHiddenInGame(false);
		bIsRolling = true;
		RollResult = 0;

		PlayerID = OwnerID;

		DieMesh->AddImpulseAtLocation(Impulse * FVector(FMath::FRandRange(-1.f,1.f), FMath::FRandRange(-1.f, 1.f), 1.0f), FMath::RandPointInBox(DiceDimensions));

		GetWorldTimerManager().SetTimer(RollCheck, this, &ADice::GetRoll, 0.1f, true);
	}
}

void ADice::SetImpulse(float NewImpulse)
{
	Impulse = NewImpulse;
}

// Called when the game starts or when spawned
void ADice::BeginPlay()
{
	Super::BeginPlay();
	
	DieMaterial = UMaterialInstanceDynamic::Create(DieMesh->GetMaterial(0), this);
	DieMesh->SetMaterial(0, DieMaterial);
	DieDotMaterial = UMaterialInstanceDynamic::Create(DieMesh->GetMaterial(1), this);
	DieMesh->SetMaterial(1, DieDotMaterial);
}

void ADice::GetRoll()
{
	if (GetVelocity().IsNearlyZero(0.1f))
	{
		for (int i = 0; i < FaceNormals.Num(); ++i)
		{
			FVector transformedvector = GetActorTransform().TransformVector(FaceNormals[i]);
			float Dot = FVector::DotProduct(transformedvector, FVector(0.0f, 0.0f, 1.0f));
			if (FMath::IsNearlyEqual(Dot, 1.0f, 0.01f))
			{
				RollResult = i + 1;
				break;
			}
		}
		GetWorldTimerManager().ClearTimer(RollCheck);
		GetWorldTimerManager().SetTimer(HideTimer, this, &ADice::HideDie, 15.0f, true);
		bIsRolling = false;

		OnRollComplete.Broadcast(this, PlayerID, RollResult);
	}
}

void ADice::HideDie()
{
	GetWorldTimerManager().ClearTimer(HideTimer);
	SetActorHiddenInGame(true);
}
