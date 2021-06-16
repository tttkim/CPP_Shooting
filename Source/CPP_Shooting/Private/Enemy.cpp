// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.h"
#include "EnemyMove.h"
#include "EnemyFire.h"
#include "EnemyBullet.h"
#include <Components/ArrowComponent.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ������Ʈ ���� ���̱�
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. �ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	enemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));
	enemyFire = CreateDefaultSubobject<UEnemyFire>(TEXT("EnemyFire"));

	// 3. �ѱ�
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(boxComp);

	// �Ѿ��� �ε��ؼ� �ٿ�����
	ConstructorHelpers::FClassFinder<AEnemyBullet> TempBullet(TEXT("Blueprint'/Game/Blueprints/BP_EnemyBullet'_C"));

	if (TempBullet.Succeeded())
	{
		enemyFire->bulletFactory = TempBullet.Class;
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

// �ٸ� ��ü�� ������ �� ȣ��Ǵ� �̺�Ʈ �Լ�
// ���� �װ� ���� �װ� ����
//void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	
//}



