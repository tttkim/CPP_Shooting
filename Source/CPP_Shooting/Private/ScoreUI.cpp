// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"
#include <Components/TextBlock.h>

void UScoreUI::PrintCurrentScore(int32 point)
{
	// 만약 current score ui widget 있다면
	if (Text_CurrentScore)
	{
		// point 를 할당시켜주자.
		FString scoreStr = FString::Printf(TEXT("Current Score: %d"), point);
		// ui 에 값을 할당
		Text_CurrentScore->SetText(FText::FromString(scoreStr));
		
	}
}

void UScoreUI::PrintTopScore(int32 point)
{
	// 만약 top score ui widget 있다면
	if (Text_TopScore)
	{
		// point 를 할당시켜주자.
		FString scoreStr = FString::Printf(TEXT("Top Score: %d"), point);
		// ui 에 값을 할당
		Text_TopScore->SetText(FText::FromString(scoreStr));
	}
}
