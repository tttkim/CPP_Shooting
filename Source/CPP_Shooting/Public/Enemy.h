// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// Ÿ���� ���� �̵��ϰ� �ʹ�.
// �ʿ�Ӽ� : Ÿ��
UCLASS()
class CPP_SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UEnemyMove* enemyMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UEnemyFire* enemyFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* firePosition;
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �浹 �̺�Ʈ ó�� �Լ�
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


};
