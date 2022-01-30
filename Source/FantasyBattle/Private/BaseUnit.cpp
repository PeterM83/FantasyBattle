// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUnit.h"
#include "Components/BoxComponent.h"
#include "ProceduralMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->SetIsReplicated(true);
	BoxCollision->bHiddenInGame = false;

	MovementMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("MeshComp"));
	MovementMesh->bUseAsyncCooking = true;
	MovementMesh->ContainsPhysicsTriMeshData(false);
	MovementMesh->SetupAttachment(RootComponent);

	UnitSize = FVector(100.f, 100.f, 50.f);
	BoxCollision->SetBoxExtent(UnitSize);
	FrontRow = 4;
}

void ABaseUnit::InitUnit_Implementation(FSaveGameUnitProfile UnitStruct, int32 ParentPlayerID)
{
}

bool ABaseUnit::InitUnit_Validate(FSaveGameUnitProfile UnitStruct, int32 ParentPlayerID)
{
	return true;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (LOSMaterial)
	{
		LOSMaterialInstance = UMaterialInstanceDynamic::Create(LOSMaterial, this);
		MovementMesh->SetMaterial(0, LOSMaterialInstance);
		LOSMaterialInstance->SetVectorParameterValue("Color", LOSMaterialColor);
	}
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABaseUnit::GetUnitSize()
{
	return UnitSize;
}

void ABaseUnit::GetFrontCorners(FVector& LeftCorner, FVector& RightCorner)
{
	LeftCorner = UKismetMathLibrary::TransformLocation(GetActorTransform(), FVector(UnitSize.X, -UnitSize.Y, -UnitSize.Z + 1));
	RightCorner = UKismetMathLibrary::TransformLocation(GetActorTransform(), FVector(UnitSize.X, UnitSize.Y, -UnitSize.Z + 1));
}

void ABaseUnit::GetFrontCornersLocal(FVector& LeftCorner, FVector& RightCorner)
{
	LeftCorner = FVector(UnitSize.X, -UnitSize.Y, -UnitSize.Z + 1);
	RightCorner = FVector(UnitSize.X, UnitSize.Y, -UnitSize.Z + 1);
}

void ABaseUnit::GetVertices()
{
	FVector LeftStart;
	FVector RightStart;
	int32 StartAngle = SightArc / 2;
	GetFrontCornersLocal(LeftStart, RightStart);
	int32 HalfVertices = FMath::RoundToInt(SightArc / AngleStep) / 2;	//Get number of points in half so i can use equal numbers from both corners
	FVector FrontRowDirection = (RightStart - LeftStart);
	FrontRowDirection.Normalize();
	int32 FrontSteps = FMath::CeilToInt((RightStart - LeftStart).Size() / 40);
	LOSVertices.Add(LeftStart);
	for (int i = 1; i < FrontSteps; i++)
	{
		LOSVertices.Add(LeftStart + (FrontRowDirection * (i * 40)));
	}
	LOSVertices.Add(RightStart);

	for (int i = 0; i < HalfVertices; i++)
	{
		FVector CurrentAngleDirection = GetActorForwardVector().RotateAngleAxis(-StartAngle + (i*AngleStep), FVector(0, 0, 1));
		FVector LineEndLocation = LeftStart + (CurrentAngleDirection * SightRange);
		//FVector HitResultInCharacterLocalSpace = GetActorTransform().InverseTransformPosition(LineEndLocation);
		LOSVertices.Add(LineEndLocation);
	}

	for (int i = 0; i < FrontSteps +1; i++)
	{
		FVector LineEndLocation = LOSVertices[i] + (GetActorForwardVector() * SightRange);
		//FVector HitResultInCharacterLocalSpace = GetActorTransform().InverseTransformPosition(LineEndLocation);
		LOSVertices.Add(LineEndLocation);
	}

	for (int i = 0; i < HalfVertices; i++)
	{
		FVector CurrentAngleDirection = GetActorForwardVector().RotateAngleAxis(AngleStep + (i * AngleStep), FVector(0, 0, 1));
		FVector LineEndLocation = RightStart + (CurrentAngleDirection * SightRange);
		//FVector HitResultInCharacterLocalSpace = GetActorTransform().InverseTransformPosition(LineEndLocation);
		LOSVertices.Add(LineEndLocation);
	}
	int CenterTriDiff = (FrontSteps + 1) + HalfVertices;
	for (int i = FrontSteps +1; i < LOSVertices.Num() -1; i++)
	{
		if (i < CenterTriDiff)
		{
			LOSTriangles.Add(0);
			LOSTriangles.Add(i +1);
			LOSTriangles.Add(i);
		}
		else if (i < FrontSteps + CenterTriDiff)
		{
			LOSTriangles.Add(i - CenterTriDiff);
			LOSTriangles.Add(i + 1);
			LOSTriangles.Add(i);
			LOSTriangles.Add(i - CenterTriDiff);
			LOSTriangles.Add(i - CenterTriDiff + 1);
			LOSTriangles.Add(i + 1);
		}
		else
		{
			LOSTriangles.Add(FrontSteps);
			LOSTriangles.Add(i + 1);
			LOSTriangles.Add(i);		
		}		
	}
	DrawLOSMesh();
}

void ABaseUnit::DrawLOSMesh()
{
	TArray<FVector> TempNormals;
	TArray<FVector2D> TempUV0;
	TArray<FProcMeshTangent> TempTangents;
	TArray<FLinearColor> TempVertexColors;
	MovementMesh->CreateMeshSection_LinearColor(0, LOSVertices, LOSTriangles, TempNormals, TempUV0, TempVertexColors, TempTangents, false);

}

