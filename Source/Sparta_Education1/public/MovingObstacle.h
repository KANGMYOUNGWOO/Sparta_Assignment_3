// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingObstacle.generated.h"

UCLASS()
class SPARTA_EDUCATION1_API AMovingObstacle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingObstacle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	FVector StartLocation;

	int32 MoveDirection = 1;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	FVector MoveAxis = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	float MaxRange = 500.0f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
