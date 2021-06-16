// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API USaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Data")
	int32 topScore;
};
