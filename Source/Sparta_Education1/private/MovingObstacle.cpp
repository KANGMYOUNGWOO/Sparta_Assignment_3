// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacle.h"
#include "Components/BoxComponent.h"
#include "EduGameMode.h"

// Sets default values
AMovingObstacle::AMovingObstacle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox ;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
	
	
	//RootComponent = CollisionBox;

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);

	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);

	CollisionBox->SetCollisionResponseToChannel(
		ECC_Pawn,
		ECR_Overlap);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(
	   this,
	   &AMovingObstacle::OnOverlapBegin);

	
}

// Called when the game starts or when spawned
void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	MoveAxis.Normalize();
}

void AMovingObstacle::SetGameMode(AEduGameMode* gameMode)
{
	this->GameMode = gameMode;
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

void AMovingObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	
	if(OtherActor->ActorHasTag("Player"))
	{
		Destroy();
		
		if (GameMode)
		{
			GameMode->AddPoint();
		}
	}
	

}

