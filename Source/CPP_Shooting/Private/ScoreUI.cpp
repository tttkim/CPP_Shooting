// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"
#include <Components/TextBlock.h>

void UScoreUI::PrintCurrentScore(int32 point)
{
	// ���� current score ui widget�� �ִٸ�
	if (Text_CurrentScore)
	{
		// point�� �Ҵ��������
		FString scoreStr = FString::Printf(TEXT("Current Score : %d"), point);
		// ui�� ���� �Ҵ�
		Text_CurrentScore->SetText(FText::FromString(scoreStr));
	}
	
}

void UScoreUI::PrintTopScore(int32 point)
{
	// ���� top score ui widget�� �ִٸ�
	if (Text_CurrentScore)
	{
		// point�� �Ҵ��������
		FString scoreStr = FString::Printf(TEXT("Top Score : %d"), point);
		// ui�� ���� �Ҵ�
		Text_TopScore->SetText(FText::FromString(scoreStr));
	}
}
