// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZone.h"
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include "CPP_ShootingGameModeBase.h"
#include "Bullet.h"


// Sets default values
ADestroyZone::ADestroyZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 추가
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = meshComp;
}

// Called when the game starts or when spawned
void ADestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
	meshComp->OnComponentHit.AddDynamic(this, &ADestroyZone::OnCollisionEnter);
}

// Called every frame
void ADestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZone::OnCollisionEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 만약 Player 라면 처리 안한다.
	APlayerCPP* player = Cast<APlayerCPP>(OtherActor);
	if (player != nullptr)
	{
		return;
	}

	// 부딪힌 대상이 총알이라면 탄창에 다시 넣어주자
	auto bullet = Cast<ABullet>(OtherActor);
	if (bullet)
	{
		auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->AddBullet(bullet);
	}
	// 그렇지 않으면 Destroy 원래대로 하기
	else
	{
		OtherActor->Destroy();
	}
}

