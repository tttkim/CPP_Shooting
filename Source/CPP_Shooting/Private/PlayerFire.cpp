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

	// ��� �ִ� ���� ���� �ð� �������� �Ѿ��� ��� �߻� �ϰ� �ʹ�.
	currentTime += DeltaTime;
	if (currentTime > createTime)
	{
		currentTime = 0;
		YogaFire();
	}
}

void UPlayerFire::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Fire ��ư �Է� ���ε�ó��
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerFire::YogaFire);
}

// �Ѿ˹߻� ó��
void UPlayerFire::YogaFire()
{
	// �Ѿ��� �Ѿ� ���忡�� ������.
	// ���鶧 �� �ڸ��� �ٸ� �༮�� �ִ��� ����� ������ ����
	/*FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory,
		firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation(), Param);*/

		// GameMode Ŭ������ GetBullet �� �̿��Ͽ� �Ѿ� ��������
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	// gamemode �� ���°� playing �� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	// ���� ���Ӹ�尡 �ִٸ�
	if (gameMode)
	{
		auto bullet = gameMode->GetBullet();
		if (bullet == nullptr)
		{
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}
		// �ι�° �Ѿ� ���� �ö� źâ�� �Ѿ��� ���̻� ���ٸ�
		// �߻� �� �� ���� ������ ù��° ������ �Ѿ��� �ٽ� źâ�� �ݳ��Ѵ�.
		auto bullet2 = gameMode->GetBullet();
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			PRINTLOG(TEXT("Error, Empty Bullet Object Pool!!!"));
			return;
		}

		// �ѹ� �߻��Ѵ�.
		gameMode->SetBulletActive(bullet, true);
		// ��ġ��Ų��.
		bullet->SetActorLocation(me->firePosition->GetComponentLocation());
		bullet->SetActorRotation(me->firePosition->GetComponentRotation());
		
		// �ѹ� �߻��Ѵ�.
		gameMode->SetBulletActive(bullet2, true);
		// ��ġ��Ų��.
		bullet2->SetActorLocation(me->firePosition2->GetComponentLocation());
		bullet2->SetActorRotation(me->firePosition2->GetComponentRotation());
	}
	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}
