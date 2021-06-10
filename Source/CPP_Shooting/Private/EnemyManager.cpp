// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "CPP_ShootingGameModeBase.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// gamemode 의 상태가 playing 이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	// - 일정시간에 한번씩 "적 생성" 로그를 찍고 싶다.
	// 1. 시간이 흘렀으니까
	currentTime += DeltaTime;
	// 2. 만약 경과시간이 생성시간을 초과했다면
	if (currentTime > createTime)
	{
		currentTime = 0;
		// 3. 로그찍기
		//PRINTLOG(TEXT("Create Enemy"));
		// 적을 만들고 싶다.
		// 위치는 EnemyManager 의 위치
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AEnemy>(enemyFactory,
			GetActorLocation(),
			GetActorRotation(), Param);
	}
}

