// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include <Components/SphereComponent.h>
#include "CPP_ShootingGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"
#include "Bullet.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 만들어서 붙이기
	// 1. Box Collider
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollier"));
	RootComponent = sphereComp;
	// 2. 외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	// sphereComp에 이벤트를 연결
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnTriggerEnter);
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 1. 방향이 필요하다.
	//FVector vel = GetActorForwardVector() * speed;
	FVector vel = FVector::DownVector * speed;

	FVector P0 = GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	SetActorLocation(P, true);
}


void AEnemyBullet::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerCPP>(OtherActor);

	if (!player)
	{
		return;
	}
	
	// 폭발효과 생성하기
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, OtherActor->GetActorTransform());

	// 폭발 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy();
	this->Destroy();

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// 부딪힌 녀석이 Player 라면
	if (player)
	{
		// 게임 오버 상태로 전환하고 싶다.
		gameMode->SetState(EGameState::Gameover);
	}
}


//void AEnemyBullet::OnCollisionEnter(AActor* OtherActor)
//{
//	// 폭발효과 생성하기
//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetOwner()->GetActorTransform());
//
//	// 폭발 사운드 재생
//	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);
//
//	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
//
//	auto player = Cast<APlayerCPP>(OtherActor);
//	
//	// 부딪힌 녀석이 Player 라면
//	if (player)
//	{
//		// 게임 오버 상태로 전환하고 싶다.
//		gameMode->SetState(EGameState::Gameover);
//	}
//	OtherActor->Destroy();
//}