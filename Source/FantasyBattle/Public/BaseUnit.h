// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

UCLASS()
class FANTASYBATTLE_API ABaseUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
		FVector GetUnitSize();

	UFUNCTION(BlueprintCallable)
		void GetFrontCorners(FVector& LeftCorner, FVector& RightCorner);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Line of Sight")
		float SightArc = 90;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Line of Sight")
		float AngleStep = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Line of Sight")
		float SightRange = 1000;

private:

	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UProceduralMeshComponent* MovementMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TArray<FVector> LOSVertices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TArray<int32> LOSTriangles;

	UFUNCTION(BlueprintCallable)
		void GetVertices();

	UFUNCTION(BlueprintCallable)
		void DrawLOSMesh();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
		int32 FrontRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
		FVector UnitSize;

};
