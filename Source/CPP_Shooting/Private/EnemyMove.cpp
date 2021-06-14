// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMove.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "Enemy.h"
#include "PlayerCPP.h"


// Sets default values for this component's properties
UEnemyMove::UEnemyMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	me = Cast<AEnemy>(GetOwner());
}


// Called when the game starts
void UEnemyMove::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TArray<AActor*> objs;
	// 태어날때 타겟을 찾아 놓자
	// -> UE4 에서 월드상에 있는 액터 찾기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	// for 문을 objs 를 검색
	/*for (int i=0;i<objs.Num();i++)
	{
		target = objs[0];
	}*/
	for (AActor* actor : objs)
	{
		target = actor;
	}

	// 랜덤 확률로 50% 이하 이면 타겟쪽으로 그렇지 않으면 아래로
	// -> 아래로 가되, 50% 이하 확률일때는 타겟쪽으로 가라
	// 랜덤 값
	int32 ratio = FMath::RandRange(1, 100);

	dir = FVector::DownVector;
	// 만약 랜덤 값이 50 이하면
	if (ratio <= 50)
	{
		//  -> 방향을 타겟쪽으로
		// 만약 target 에 값이 제대로 들어 있다면 이름을 출력해보자
		// 1. 방향이 필요하다.
		// dir 구할 때 target 있으면 타겟쪽으로 그렇지 않으면
		// 그리고 target 이 유효하면
		if (target && IsValid(target))
		{
			// 방향을 타겟쪽으로
			dir = target->GetActorLocation() - me->GetActorLocation();
		}
		dir.Normalize();
	}
}


// Called every frame
void UEnemyMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector vel = dir * speed;

	FVector P0 = me->GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	me->SetActorLocation(P, true);
}

