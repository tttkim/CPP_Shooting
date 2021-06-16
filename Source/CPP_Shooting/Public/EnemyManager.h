// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"


// 일정시간에 한번씩 적을 만들고 싶다.
// 필요속성 : 생성시간, 경과시간, 적공장
// - 일정시간에 한번씩 "적 생성" 로그를 찍고 싶다.
// 1. 시간이 흘렀으니까
// 2. 경과시간이 생성시간을 초과했으니까
// 3. 로그찍기
UCLASS()
class CPP_SHOOTING_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateEnemy();

	UPROPERTY()
	FTimerHandle createTimer;
public:
	// 필요속성 : 생성시간, 경과시간, 적공장
	UPROPERTY(EditAnywhere, Category="Setting")
	float createTime = 2;
	UPROPERTY()
	float currentTime = 0;

	// 공장
	UPROPERTY(EditDefaultsOnly, Category = "EnemyClass")
	TSubclassOf<class AEnemy> enemyFactory;
};
