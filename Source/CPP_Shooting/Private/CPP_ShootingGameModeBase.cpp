// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"
#include "CPP_Shooting.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "PlayerCPP.h"
#include <Blueprint/UserWidget.h>
#include "ScoreUI.h"
#include "SaveData.h"

ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	// Tick �Լ��� ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = NULL;

	// źâ ũ�� ��������
	bulletPoolSize = 10;
}

void ACPP_ShootingGameModeBase::InitGameState()
{
	Super::InitGameState();

	// ȭ�鿡 Enemy �� ������ �� �������ش�.
	/*
	TArray<AActor*> objs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), objs);
	for (auto obj:objs)
	{
		AEnemy* enemy = Cast<AEnemy>(obj);
		enemy->Destroy();
	}
	*/
	for (TActorIterator<AEnemy> it( GetWorld() ) ; it; ++it )
	{
		it->Destroy();
	}

	// ȭ�鿡 �Ѿ��� ������ �� Ǯ�� �־��ش�.
	// 1. ���忡 �ִ� �Ѿ��� ã�ƾ� �Ѵ�.
	for (TActorIterator<ABullet> it(GetWorld()); it; ++it)
	{
		// 2. źâ �ۿ� �ִ� �Ѿ��� �ϳ� �����´�.		
		ABullet* bullet = *it;
		// 3. �Ѿ��� Ǯ(źâ)�� �־��ְ� �ʹ�.
		AddBullet(bullet);
	}
	// Player �� ������ ���������.
	// 1. ���� ã�ƺðŵ�
	//AActor* playerObj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	// 2. Player �� �����ϱ�
	//if (playerObj == nullptr)
	// ���°� gameover ���
	if(mState == EGameState::Gameover)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// 3. Player �� ����� �ʹ�.
		auto player = GetWorld()->SpawnActor<APlayerCPP>(DefaultPawnClass, FVector::ZeroVector, FRotator::ZeroRotator, param);

		// 4. PlayerController �� ����(���� Possess)�ǵ��� ����
		GetWorld()->GetFirstPlayerController()->Possess(player);
	}
	// ������ ���¸� Ready �� ������ ����.
	mState = EGameState::Ready;

	// readyUI �� �ִٸ� ȭ�鿡 ������ֱ�
	// -> reset ��ư�� ������ ��
	if (readyUI)
	{
		readyUI->AddToViewport();
	}

	// ������ �ε��ϱ�
	// savedata ����
	saveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("Score"), 0));

	//// Score �����Ͱ� �����ϴ��� �����ϱ�
	// bool isExist = UGameplayStatics::DoesSaveGameExist(TEXT("Score"), 0);

	// ���� ���� �����Ͱ� ������
	if (saveData == nullptr)
	{
		// SaveData �ϳ� �����
		auto saveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		saveData = Cast<USaveData>(saveGame);
		saveData->topScore = 0;
		// ���� ������ ������ش�
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("Score"), 0);
	}
	// ����Ǿ� �ִ� score�� �ҷ�����
	topScore = saveData->topScore;
	// ui�� ǥ�����ֱ�
	// scoreUI �����ϰ� �������
	scoreUI = CreateWidget<UScoreUI>(GetWorld(), scoreUIFactory);
	if (scoreUI)
	{
		scoreUI->AddToViewport();
		// top score�� ui�� ǥ��
		scoreUI->PrintCurrentScore(curScore);
		scoreUI->PrintTopScore(topScore);
	}
}

void ACPP_ShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	
	// �Ѿ� ���� �ּҰ� ���ٸ�
	if (bulletFactory)
	{
		// źâ�� �Ѿ� ���� ����
		for (int32 i = 0; i < bulletPoolSize; ++i)
		{
			ABullet* bullet = CreateBullet();

			if (bullet)
			{
				AddBullet(bullet);
			}
		}
	}

	// �¾ �� Ready UI �����
	// ���� Ready UI ������ �ִٸ�
	if (readyUIFactory)
	{
		// Ready UI �� �ϳ� ����� �ʹ�.
		readyUI = CreateWidget<UUserWidget>(GetWorld(), readyUIFactory);
		// ȭ�鿡 UI �� ���̵��� �ϱ�
		readyUI->AddToViewport();
	}

	// �¾ �� Start UI �����
	// ���� Start UI ������ �ִٸ�
	if (startUIFactory)
	{
		// Start UI �� �ϳ� ����� �ʹ�.
		startUI = CreateWidget<UUserWidget>(GetWorld(), startUIFactory);
	}

	// �¾ �� Gameover UI �����
	// ���� Gameover UI ������ �ִٸ�
	if (gameoverUIFactory)
	{
		// gameover UI �� �ϳ� ����� �ʹ�.
		gameoverUI = CreateWidget<UUserWidget>(GetWorld(), gameoverUIFactory);
	}


}

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// �������� ����
	//if (mState == EGameState::Ready)
	//{
	//	// to do
	//}
	//else if (mState == EGameState::Playing)
	//{
	//	// to do
	//}
	//else if (mState == EGameState::Gameover)
	//{
	//	// to do
	//}
	//else
	//{
	//	// to do
	//}
	
	//// ���� ���¸� ����� ���� �ʹ�.
	/*const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)mState));
	}*/
	//PrintEnumData(mState);

	switch (mState)
	{
	case EGameState::Ready:
		ReadyPage();
		break;
	case EGameState::Playing:
		PlayingPage();
		break;
	case EGameState::Gameover:
		GameoverPage();
		break;
	}
}

// �����ð� ��ٷȴٰ� ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
// -> Ready �ؽ�Ʈ ǥ���ϱ� log
// �ʿ�Ӽ� : (���ð�)�����ð�, ����ð�
void ACPP_ShootingGameModeBase::ReadyPage()
{
	//PRINTLOG(TEXT("READY STATE"));
	// �����ð� ��ٷȴٰ� ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. �����ð��� �����ϱ�
	// 	   ���� ����ð��� ���ð��� �ʰ��Ͽ��ٸ�
	if (currentTime > readyDelayTime)
	{
		// 3. ���¸� Playing ���� ��ȯ�ϰ� �ʹ�.
		mState = EGameState::Playing;
		currentTime = 0;

		// ȭ�鿡 �ִ� ready ui �� ���� �ϰ� �ʹ�.
		if (readyUI)
		{
			readyUI->RemoveFromViewport();
		}

		if (startUI)
		{
			startUI->AddToViewport();
		}
	}
}
// Start �ؽ�Ʈ ǥ���ϱ�
// Start �ؽ�Ʈ�� 2���� �������.
// ���� �����ϰ� �Ѵ�.
void ACPP_ShootingGameModeBase::PlayingPage()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. �����ð��� �����ϱ�
	// 	   ���� ����ð��� ���ð��� �ʰ��Ͽ��ٸ�
	if (currentTime > startUITime)
	{
		startUI->RemoveFromViewport();
		currentTime = 0;
	}
}
// Gameover �޴�ǥ���ϱ�
// R Ű�� ������ �ٽ� ���� ��Ű��
void ACPP_ShootingGameModeBase::GameoverPage()
{
	// R Ű�� �Է� �ޱ�
	// 1. PlayerController ��������
	APlayerController* myController = GetWorld()->GetFirstPlayerController();
	//APlayerController* myController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 2. Ű�Է� ó�� -> RŰ�� �����ٸ�
	// myController �� �ְ� R Ű�� �����ٸ�
	if (myController && myController->WasInputKeyJustPressed(EKeys::R))
	{
		PRINTLOG(TEXT("R Key Pressed!!!!!!!!!!!!"));
		ResetLevel();
	}
}

void ACPP_ShootingGameModeBase::SetBulletActive(ABullet* bullet, bool isActive)
{
	bullet->SetActorHiddenInGame(!isActive);
	bullet->SetActorEnableCollision(isActive);
	bullet->SetActorTickEnabled(isActive);
}

void ACPP_ShootingGameModeBase::AddBullet(ABullet* bullet, bool bTest)
{
	// 2. źâ�� �Ѿ��� �ִ´�.
	bulletPool.AddUnique(bullet);

	if (bTest)
	{
		PRINTLOG(TEXT("Count : %d"), bulletPool.Num());
	}

	// 3. �Ѿ��� ��Ȱ��ȭ ��Ų��.
	SetBulletActive(bullet, false);
}

ABullet* ACPP_ShootingGameModeBase::GetBullet()
{
	// źâ���� �Ѿ��� �ϳ� ������ �ʹ�.
	/*
	for (int32 i = 0;i<bulletPoolSize;++i)
	{
		// �Ⱥ��δ�. -> ��Ȱ��ȭ
		if (bulletPool[i]->IsHidden())
		{
			ABullet* bullet = bulletPool[i];
			bulletPool.RemoveAt(0);
			return bullet;
		}
	}*/
	/*
	// �迭�� ���� �ϳ� �̸��̶�� null �� ��ȯ
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}

	// 1. Ǯ���� �Ѿ��� �ϳ� ������
	ABullet* bullet = bulletPool[0];
	// 2. źâ���� ���� �Ѿ� ���ֱ�
	bulletPool.RemoveAt(0);
	// -> RemoveAt
	// 3. �Ѿ��� ��ȯ���ֱ�
	return bullet;
	*/
	// Ǯ�� �Ѿ��� ���ٸ� null ����
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}
	ABullet* bullet = bulletPool.Pop();
	return bullet;
}

void ACPP_ShootingGameModeBase::PrintEnumData_Implementation(EGameState value)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)value));
	}
}

ABullet* ACPP_ShootingGameModeBase::CreateBullet()
{	
	// 1. �Ѿ˰��忡�� �Ѿ��� �����.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}

void ACPP_ShootingGameModeBase::SetCurrentScore(int32 point)
{
	// ���� ���� ����
	curScore = point;
	// UI�� ǥ���ϰ� �ʹ�
	// 1. scoreui factory���� scoreui �ϳ� ������ �Ѵ�
	// 2. scoeui�� ui widget�� ���� �Ҵ��ϰ� �ʹ�
	scoreUI->PrintCurrentScore(curScore);

	// ���� ������ �ְ� ������ �Ѿ��
	if (curScore > topScore)
	{
		// ���� ������ �ְ� ������ �ȴ�.
		topScore = curScore;
		// topscore ui ����
		scoreUI->PrintTopScore(topScore);

		saveData->topScore = topScore;
		// �����͸� ����
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("Score"), 0);
	}
}

int32 ACPP_ShootingGameModeBase::GetCurrentScore()
{
	return curScore;
}

void ACPP_ShootingGameModeBase::SetState(EGameState s)
{
	mState = s;
	// ���� ����� ���°� Gameover��� widget ��������
	if (mState == EGameState::Gameover)
	{
		// ���� �Ͻ� ����
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		// ���콺Ŀ�� ���̵��� ��
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

		gameoverUI->AddToViewport();
	}
}
