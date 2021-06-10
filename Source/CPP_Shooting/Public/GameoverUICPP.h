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

	// UI widget ��������
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Restart;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Quit;

	// Blueprint ���� �ش� �Լ��� ȣ���� �� �ֵ��� ����
	UFUNCTION(BlueprintCallable)
	void Restart();

	UFUNCTION(BlueprintCallable)
	void Quit();
};
