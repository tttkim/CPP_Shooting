// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"


// �����ð��� �ѹ��� ���� ����� �ʹ�.
// �ʿ�Ӽ� : �����ð�, ����ð�, ������
// - �����ð��� �ѹ��� "�� ����" �α׸� ��� �ʹ�.
// 1. �ð��� �귶���ϱ�
// 2. ����ð��� �����ð��� �ʰ������ϱ�
// 3. �α����
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


public:
	// �ʿ�Ӽ� : �����ð�, ����ð�, ������
	UPROPERTY(EditAnywhere, Category="Setting")
	float createTime = 2;
	UPROPERTY()
	float currentTime = 0;

	// ����
	UPROPERTY(EditDefaultsOnly, Category = "EnemyClass")
	TSubclassOf<class AEnemy> enemyFactory;
};
