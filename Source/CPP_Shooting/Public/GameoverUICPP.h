// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameoverUICPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UGameoverUICPP : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnQuitClicked();

	// UI widget 가져오기
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* Button_Restart;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* Button_Quit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* tempButton;

	// Blueprint 에서 해당 함수를 호출 할 수 있도록 설정
	UFUNCTION(BlueprintCallable)
	void Restart();

	UFUNCTION(BlueprintCallable)
	void Quit();
};
