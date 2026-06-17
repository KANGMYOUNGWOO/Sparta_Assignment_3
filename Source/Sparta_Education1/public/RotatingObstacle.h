// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RotatingObstacle.generated.h"

UCLASS()
class SPARTA_EDUCATION1_API ARotatingObstacle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARotatingObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
     
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator RotationSpeed = FRotator(0.0f, 90.0f, 0.0f);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
