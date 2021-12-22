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

	UFUNCTION(BlueprintCallable)
		void GetFrontCornersLocal(FVector& LeftCorner, FVector& RightCorner);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UProceduralMeshComponent* MovementMesh;

	UFUNCTION(BlueprintCallable)
		void GetVertices();

	UFUNCTION(BlueprintCallable)
		void DrawLOSMesh();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		TArray<FVector> LOSVertices;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		TArray<int32> LOSTriangles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		float SightArc = 90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		float AngleStep = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		float SightRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		FLinearColor LOSMaterialColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Line of Sight", meta = (AllowPrivateAccess = "true"))
		UMaterialInterface* LOSMaterial;

		UMaterialInstanceDynamic* LOSMaterialInstance;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
		int32 FrontRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
		FVector UnitSize;

};
