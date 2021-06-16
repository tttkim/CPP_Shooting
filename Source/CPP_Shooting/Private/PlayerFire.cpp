// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"
#include <Kismet/GameplayStatics.h>
#include <Components/ArrowComponent.h>

// Sets default values for this component's properties
UPlayerFire::UPlayerFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());
}




// Called every frame
void UPlayerFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 살아 있는 동안 일정 시간 간격으로 총알을 계속 발사 하고 싶다.
	currentTime += DeltaTime;
	if (currentTime > createTime)
	{
		currentTime = 0;
		YogaFire();
	}
}

void UPlayerFire::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Fire 버튼 입력 바인딩처리
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerFire::YogaFire);
}

// 총알발사 처리
void UPlayerFire::YogaFire()
{
	// 총알을 총알 공장에서 만들자.
	// 만들때 그 자리에 다른 녀석이 있더라도 만들어 지도록 설정
	/*FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(), Param);*/

		// GameMode 클래스의 GetBullet 을 이용하여 총알 가져오기
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// gamemode 의 상태가 playing 이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	// 만약 게임모드가 있다면
	if (gameMode)
	{
		auto bullet = gameMode->GetBullet();
		if (bullet == nullptr)
		{
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}
		// 두번째 총알 가져 올때 탄창에 총알이 더이상 없다면
		// 발사 할 수 없기 때문에 첫번째 가져온 총알은 다시 탄창에 반납한다.
		auto bullet2 = gameMode->GetBullet();
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}

		// 한발 발사한다.
		gameMode->SetBulletActive(bullet, true);
		// 배치시킨다.
		bullet->SetActorLocation(me->firePosition->GetComponentLocation());
		bullet->SetActorRotation(me->firePosition->GetComponentRotation());
		
		// 한발 발사한다.
		gameMode->SetBulletActive(bullet2, true);
		// 배치시킨다.
		bullet2->SetActorLocation(me->firePosition2->GetComponentLocation());
		bullet2->SetActorRotation(me->firePosition2->GetComponentRotation());
	}
	// 총알 발사 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}
