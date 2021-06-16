// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Text_CurrentScore;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_TopScore;

	// Current Score 출력하는 함수
	void PrintCurrentScore(int32 point);
	// Top Score 출력하는 함수
	void PrintTopScore(int32 point);
};
