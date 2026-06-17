// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacle.h"

// Sets default values
AMovingObstacle::AMovingObstacle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	
}

// Called when the game starts or when spawned
void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	MoveAxis.Normalize();
}

// Called every frame
void AMovingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	
	float DistanceFromStart = FVector::DotProduct(CurrentLocation - StartLocation, MoveAxis);
	
	if(FMath::Abs(DistanceFromStart) > MaxRange) MoveDirection *= -1;
	
	FVector MoveOffset = MoveAxis * MoveSpeed * MoveDirection * DeltaTime;
	
	AddActorWorldOffset(MoveOffset,true);
	
	
}

// Called to bind functionality to input
void AMovingObstacle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

