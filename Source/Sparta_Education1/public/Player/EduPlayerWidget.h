// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EduPlayerWidget.generated.h"

class UTextBlock; 

/**
 * 
 */
UCLASS()
class SPARTA_EDUCATION1_API UEduPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	
	void  SetWaveText(int32 Wave);
	
	void  SetLevelText(int32 Level);
	
	void  SetTimeText(float Time);
	
	void SetScoreText(int32 Score);
protected :
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeLeftBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>  ScoreBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>  WaveBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>  LevelBlock;
	
};
