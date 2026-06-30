// Fill out your copyright notice in the Description page of Project Settings.


#include "EduGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EduPlayerWidget.h"
#include  "MovingObstacle.h"

void AEduGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}
	
	PlayerWidget = CreateWidget<UEduPlayerWidget>(PC, PlayerWidgetClass);
	
	PlayerWidget->AddToViewport();
	
	
	
	StartWave();
}

void AEduGameMode::StartWave()
{
	PlayerWidget->SetLevelText(CurrentLevel);
	PlayerWidget->SetWaveText(CurrentWave);
	PlayerWidget->SetScoreText(Score);
	UE_LOG(LogTemp, Warning,
		   TEXT("Level %d Wave %d Start"),
		   CurrentLevel,
		   CurrentWave);
	
	GEngine ->AddOnScreenDebugMessage(-1,3.f,FColor::Green,
		FString::Printf(TEXT("Wave %d 시작"),CurrentWave));
	
	GetWorld()->GetTimerManager().SetTimer(WaveTimer,
		this,&AEduGameMode::EndWave,
		WaveTime,
		false);
	
	GetWorld()->GetTimerManager().SetTimer(
	UITimer,
	this,
	&AEduGameMode::UpdateTime,
	0.1f,
	true);
	
	for (int i=0; i<CurrentWave *5 + CurrentLevel *3; i++)
	{
		SpawnObstacle();
	}
	
}

void AEduGameMode::EndWave()
{
	CurrentWave++;
	GetWorld()->GetTimerManager().ClearTimer(UITimer);
	if (CurrentWave > 3)
	{
		CurrentWave = 1;
		CurrentLevel++;
	}
	
	if (CurrentLevel > 3)
	{
		GameOver();
		return;
	}
	WaveTime -= 5.f;
	SpawnCount += 5;
	
	for (AMovingObstacle* Obstacle : Obstacles)
	{
		if (IsValid(Obstacle))
		{
			Obstacle->Destroy();
		}
	}

	Obstacles.Empty();
	
	StartWave();
}

void AEduGameMode::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Clear"));

	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Yellow,
		TEXT("Game Clear"));
}

void AEduGameMode::SpawnObstacle()
{
	AMovingObstacle* Obstacle;
	
	if (!MovingObstacleClass)
	{
		return;
	}

	FVector SpawnLocation;

	SpawnLocation.X = FMath::RandRange(-1000.f, 1000.f);
	SpawnLocation.Y = FMath::RandRange(-1000.f, 1000.f);
	SpawnLocation.Z = 100.f;

	Obstacle = GetWorld()->SpawnActor<AMovingObstacle>(
		MovingObstacleClass,
		SpawnLocation,
		FRotator::ZeroRotator);
	Obstacle->SetGameMode(this);
	if (IsValid(Obstacle))
	{
		Obstacles.Add(Obstacle);
	}

	
}

void AEduGameMode::UpdateTime()
{
	if (!PlayerWidget)
	{
		return;
	}

	float Remaining =
		GetWorld()->GetTimerManager().GetTimerRemaining(WaveTimer);

	PlayerWidget->SetTimeText(Remaining);
}

void AEduGameMode::AddPoint()
{
	Score += 10;
	
	if (!PlayerWidget)
	{
		return;
	}
	PlayerWidget->SetScoreText(Score);
}
