// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingObstacle.h"

// Sets default values
ARotatingObstacle::ARotatingObstacle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp")); 
}

// Called when the game starts or when spawned
void ARotatingObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  AddActorLocalRotation(RotationSpeed * DeltaTime);
}

// Called to bind functionality to input
void ARotatingObstacle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

