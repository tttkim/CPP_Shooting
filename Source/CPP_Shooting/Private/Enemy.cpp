// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "CPP_ShootingGameModeBase.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���� ���̱�
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. �ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
	// ������Ʈ �浹�� ����� �̺�Ʈ �Լ��� ��������ְ� �ʹ�.
	// �ʿ��Ѱ� : ó���� �̺�Ʈ �Լ�
	// -> ������Ʈ �浹�� ���ؼ��� AddDynamic �Լ��� �̿��ؾ� �Ѵ�.
	// -> AddDynamic �Լ��� ���ڷ� ��ϵǴ� �̺�Ʈ �Լ��� �ݵ�� UFUNCTION ��ũ�θ� ����ؾ� �Ѵ�.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnTriggerEnter);

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
			dir = target->GetActorLocation() - GetActorLocation();
		}
		dir.Normalize();
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector vel = dir * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. ��ġ�� �����ϰ� �ʹ�. -> �̵��ϰ��ʹ�.
	SetActorLocation(P, true);
}

// �ٸ� ��ü�� ������ �� ȣ��Ǵ� �̺�Ʈ �Լ�
// ���� �װ� ���� �װ� ����
//void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	
//}

void AEnemy::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ������ �浹 ���� �ʵ��� �ϰ� �ʹ�.
	// 1. �̸���
	// 2. �ε��� ����� Enemy �� Type casting �Ѵ�.
	// OtherActor �� AEnemy �� ����ȯ �ؼ� �� �ȵǸ� NULL �� ��ȯ�Ѵ�.
	// �ε��� �༮�� ���̶��??
	// -> ���� enemy �� Null �� �ƴ� ���
	//AEnemy* enemy = Cast<AEnemy>(OtherActor);
	//if (enemy != nullptr)
	//{
	//	// -> �Ʒ� ������ ���̻� ó���ϰ� ���� �ʴ�.
	//	return;
	//}
	/*if ( OtherActor->GetName().Contains(TEXT("Enemy")) )
	{
		return;
	}*/

	// ����ȿ�� �����ϱ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// ���� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy();
	Destroy();
}

void AEnemy::OnCollisionEnter(AActor* OtherActor)
{
	// ����ȿ�� �����ϱ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// ���� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	
	// �ε��� ����� �Ѿ��̶�� źâ�� �ٽ� �־�����
	auto bullet = Cast<ABullet>(OtherActor);
	if (bullet)
	{
		gameMode->AddBullet(bullet, true);
	}
	// �׷��� ������ Destroy ������� �ϱ�
	else
	{
		// �ε��� �༮�� Player ���
		auto player = Cast<APlayerCPP>(OtherActor);

		if (player)
		{
			// ���� ���� ���·� ��ȯ�ϰ� �ʹ�.
			gameMode->SetState(EGameState::Gameover);
		}
		OtherActor->Destroy();
	}
	// ���� �÷�����
	gameMode->SetCurrentScore(gameMode->GetCurrentScore() + 1);

	Destroy();
}
