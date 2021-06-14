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
	// �¾�� Ÿ���� ã�� ����
	// -> UE4 ���� ����� �ִ� ���� ã��
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	// for ���� objs �� �˻�
	/*for (int i=0;i<objs.Num();i++)
	{
		target = objs[0];
	}*/
	for (AActor* actor : objs)
	{
		target = actor;
	}

	// ���� Ȯ���� 50% ���� �̸� Ÿ�������� �׷��� ������ �Ʒ���
	// -> �Ʒ��� ����, 50% ���� Ȯ���϶��� Ÿ�������� ����
	// ���� ��
	int32 ratio = FMath::RandRange(1, 100);

	dir = FVector::DownVector;
	// ���� ���� ���� 50 ���ϸ�
	if (ratio <= 50)
	{
		//  -> ������ Ÿ��������
		// ���� target �� ���� ����� ��� �ִٸ� �̸��� ����غ���
		// 1. ������ �ʿ��ϴ�.
		// dir ���� �� target ������ Ÿ�������� �׷��� ������
		// �׸��� target �� ��ȿ�ϸ�
		if (target && IsValid(target))
		{
			// ������ Ÿ��������
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
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ�ʹ�.
	me->SetActorLocation(P, true);
}

