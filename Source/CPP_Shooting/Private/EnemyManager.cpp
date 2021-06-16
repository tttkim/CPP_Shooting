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
	
	// 타이머 맞추기
	GetWorld()->GetTimerManager().SetTimer(createTimer, this, &AEnemyManager::CreateEnemy, createTime, true, 0);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	//if (gameMode->GetState() == EGameState::Gameover)
	//{
	//	// 타이머 끄기
	//	GetWorld()->GetTimerManager().ClearTimer(createTimer);
	//}

	// gamemode 의 상태가 playing 이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemy>(enemyFactory,
		GetActorLocation(),
		GetActorRotation(), Param);
}

