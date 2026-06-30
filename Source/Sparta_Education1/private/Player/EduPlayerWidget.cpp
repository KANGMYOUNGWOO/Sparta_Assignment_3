// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EduPlayerWidget.h"
#include "Components/TextBlock.h"

void UEduPlayerWidget::SetWaveText(int32 Wave)
{
	WaveBlock->SetText(FText::Format(
	FText::FromString(TEXT("현재 웨이브 {0}")),Wave	
	));
}

void UEduPlayerWidget::SetLevelText(int32 Level)
{
	LevelBlock->SetText(FText::Format(
	FText::FromString(TEXT("현재 레벨 {0}")),Level	
	));
}

void UEduPlayerWidget::SetTimeText(float Time)
{
	TimeLeftBlock->SetText(
	  FText::AsNumber(FMath::CeilToInt(Time))
  );
}

void UEduPlayerWidget::SetScoreText(int32 Score)
{
	ScoreBlock->SetText(FText::Format(
	FText::FromString(TEXT("현재 점수 {0}")),Score
	));
}


