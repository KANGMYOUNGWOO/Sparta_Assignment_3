// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EduGameMode.generated.h"


class AMovingObstacle;
class UEduPlayerWidget;
/**
 * 
 */
UCLASS()
class SPARTA_EDUCATION1_API AEduGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	
public :
	
	virtual void BeginPlay() override;
	
	void StartWave();
	
	void EndWave();
	
	void GameOver();
	
	void AddPoint();
	
	
	
	
private :
	
	int32 CurrentLevel = 1;
	
	int32 CurrentWave = 1;
	
	float WaveTime = 30.0f;
	
	int32 SpawnCount = 5;
	
	int32 Score = 0;
	
	FTimerHandle WaveTimer;
	FTimerHandle UITimer;
	
	UFUNCTION()
	void SpawnObstacle();
	
	UFUNCTION()
	void UpdateTime();
	
	UPROPERTY(EditAnywhere, Category = "Shop")
	TSubclassOf<UEduPlayerWidget> PlayerWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UEduPlayerWidget> PlayerWidget;
	
	UPROPERTY(EditAnywhere, Category = "Shop")
	TSubclassOf<AMovingObstacle> MovingObstacleClass;
	
	TArray<AMovingObstacle*> Obstacles;
	
	
	
};


