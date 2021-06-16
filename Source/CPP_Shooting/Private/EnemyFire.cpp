// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFire.h"
#include "Enemy.h"
#include <Components/ArrowComponent.h>
#include "EnemyBullet.h"

// Sets default values for this component's properties
UEnemyFire::UEnemyFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEnemyFire::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AEnemy>(GetOwner());

	Fire();
}


// Called every frame
void UEnemyFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyFire::Fire()
{
	// 총알을 하나 발사하고 싶다
	// -> 만들고 싶다
	// -> 위치시키고 싶다.
	// fireposition
	
	auto firePosition = me->firePosition;
	
	FActorSpawnParameters params;
	
	if (me && bulletFactory)
	{
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemyBullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
	}
}
