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

	// 컴포넌트 만들어서 붙이기
	// 1. Box Collider
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollier"));
	RootComponent = boxComp;
	// 2. 외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
		
	// 컴포넌트 충돌을 담당할 이벤트 함수를 연결시켜주고 싶다.
	// 필요한것 : 처리할 이벤트 함수
	// -> 컴포넌트 충돌을 위해서는 AddDynamic 함수를 이용해야 한다.
	// -> AddDynamic 함수의 인자로 등록되는 이벤트 함수는 반드시 UFUNCTION 매크로를 사용해야 한다.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnTriggerEnter);

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
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	SetActorLocation(P, true);
}

// 다른 물체와 겹쳤을 때 호출되는 이벤트 함수
// 갸도 죽고 나도 죽게 하자
//void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	
//}

void AEnemy::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 적끼리 충돌 하지 않도록 하고 싶다.
	// 1. 이름비교
	// 2. 부딪힌 대상을 Enemy 로 Type casting 한다.
	// OtherActor 를 AEnemy 로 형변환 해서 잘 안되면 NULL 을 반환한다.
	// 부딪힌 녀석이 적이라면??
	// -> 만약 enemy 가 Null 이 아니 라면
	//AEnemy* enemy = Cast<AEnemy>(OtherActor);
	//if (enemy != nullptr)
	//{
	//	// -> 아래 내용을 더이상 처리하고 싶지 않다.
	//	return;
	//}
	/*if ( OtherActor->GetName().Contains(TEXT("Enemy")) )
	{
		return;
	}*/

	// 폭발효과 생성하기
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// 폭발 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy();
	Destroy();
}

void AEnemy::OnCollisionEnter(AActor* OtherActor)
{
	// 폭발효과 생성하기
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorTransform());

	// 폭발 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	
	// 부딪힌 대상이 총알이라면 탄창에 다시 넣어주자
	auto bullet = Cast<ABullet>(OtherActor);
	if (bullet)
	{
		gameMode->AddBullet(bullet, true);
	}
	// 그렇지 않으면 Destroy 원래대로 하기
	else
	{
		// 부딪힌 녀석이 Player 라면
		auto player = Cast<APlayerCPP>(OtherActor);

		if (player)
		{
			// 게임 오버 상태로 전환하고 싶다.
			gameMode->SetState(EGameState::Gameover);
		}
		OtherActor->Destroy();
	}
	// 점수 올려주자
	gameMode->SetCurrentScore(gameMode->GetCurrentScore() + 1);

	Destroy();
}

