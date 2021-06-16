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
	// Tick 함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = NULL;

	// 탄창 크기 정해주자
	bulletPoolSize = 10;
}

void ACPP_ShootingGameModeBase::PlayingProcess(float value)
{
	// 3. ui 없애주자
	startUI->RemoveFromViewport();
	currentTime = value;
}

void ACPP_ShootingGameModeBase::InitGameState()
{
	Super::InitGameState();

	// 화면에 Enemy 가 있으면 다 제거해준다.
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

	// 화면에 총알이 있으면 다 풀에 넣어준다.
	// 1. 월드에 있는 총알을 찾아야 한다.
	for (TActorIterator<ABullet> it(GetWorld()); it; ++it)
	{
		// 2. 탄창 밖에 있는 총알을 하나 가져온다.		
		ABullet* bullet = *it;
		// 3. 총알을 풀(탄창)에 넣어주고 싶다.
		AddBullet(bullet);
	}
	// Player 가 없으면 만들어주자.
	// 1. 내가 찾아봤거든
	//AActor* playerObj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	// 2. Player 가 없으니까
	//if (playerObj == nullptr)
	// 상태가 gameover 라면
	if(mState == EGameState::Gameover)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// 3. Player 를 만들고 싶다.
		auto player = GetWorld()->SpawnActor<APlayerCPP>(DefaultPawnClass, FVector::ZeroVector, FRotator::ZeroRotator, param);

		// 4. PlayerController 가 빙의(소유 Possess)되도록 하자
		GetWorld()->GetFirstPlayerController()->Possess(player);
	}
	// 게임의 상태를 Ready 로 설정해 주자.
	//mState = EGameState::Ready;
	SetState(EGameState::Ready);

	// readyUI 가 있다면 화면에 출력해주기
	// -> reset 버튼이 눌렸을 때
	if (readyUI)
	{
		readyUI->AddToViewport();
	}

	if (gameoverUI)
	{
		gameoverUI->RemoveFromViewport();
	}
	// 데이터 로드하기
	// 1. InitGameState
	// -> SaveData 로드
	saveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("TopScore"), 0));
	// -> 만약 저장데이터가 없으면
	if(saveData == nullptr)
	{
		// SaveData 하나 만든다.
		auto saveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		saveData = Cast<USaveData>(saveGame);
		saveData->topScore = 0;
		// 저장 슬롯 만들어준다.
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"), 0);
	}

	// -> topScore 에 로드된 데이터 할당
	topScore = saveData->topScore;
	curScore = 0;
	if (scoreUI)
	{
		// ui 에 표시해주기
		scoreUI->PrintCurrentScore(curScore);
		scoreUI->PrintTopScore(topScore);
	}
}

void ACPP_ShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 함수 델리게이트 연결
	playingStateDelegate.BindUObject(this, &ACPP_ShootingGameModeBase::PlayingProcess);

	// 총알 공장 주소가 없다면
	if (bulletFactory)
	{
		// 탄창에 총알 만들어서 넣자
		for (int32 i = 0; i < bulletPoolSize; ++i)
		{
			ABullet* bullet = CreateBullet();

			if (bullet)
			{
				AddBullet(bullet);
			}
		}
	}

	// 태어날 때 Ready UI 만들기
	// 만약 Ready UI 공장이 있다면
	if (readyUIFactory)
	{
		// Ready UI 를 하나 만들고 싶다.
		readyUI = CreateWidget<UUserWidget>(GetWorld(), readyUIFactory);
		// 화면에 UI 가 보이도록 하기
		readyUI->AddToViewport();
	}

	// start UI 만들자
	if (startUIFactory)
	{
		startUI = CreateWidget<UUserWidget>(GetWorld(), startUIFactory);
	}

	// start UI 만들자
	if (gameoverUIFactory)
	{
		gameoverUI = CreateWidget<UUserWidget>(GetWorld(), gameoverUIFactory);
	}

	// scoreui 생성하고 등록하자
	scoreUI = CreateWidget<UScoreUI>(GetWorld(), scoreUIFactory);
	if (scoreUI)
	{
		scoreUI->AddToViewport();
		// top Score 를 ui 에 표시
		scoreUI->PrintCurrentScore(curScore);
		scoreUI->PrintTopScore(topScore);
	}
}

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// 상태제어 설계
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
	
	//// 현재 상태를 출력해 보고 싶다.
	/*const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumPtr)
	{
		PRINTLOG(TEXT("State : %s"), *enumPtr->GetNameStringByValue((uint8)mState));
	}*/
	//PrintEnumData(mState);

	switch (mState)
	{
	case EGameState::Ready:
		//ReadyPage();
		break;
	case EGameState::Playing:
		PlayingPage();
		break;
	case EGameState::Gameover:
		GameoverPage();
		break;
	}
}

// 일정시간 기다렸다가 상태를 Playing 으로 전환하고 싶다.
// -> Ready 텍스트 표현하기 log
// 필요속성 : (대기시간)일정시간, 경과시간
void ACPP_ShootingGameModeBase::ReadyPage()
{
	//PRINTLOG(TEXT("READY STATE"));
	// 일정시간 기다렸다가 상태를 Playing 으로 전환하고 싶다.
	// 1. 시간이 흘렀으니까
	//currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 일정시간이 됐으니까
	// 	   만약 경과시간이 대기시간을 초과하였다면
	//if (currentTime > readyDelayTime)
	{
		// 3. 상태를 Playing 으로 전환하고 싶다.
		//GetWorld()->GetTimerManager().ClearTimer(readyTimer);
		SetState(EGameState::Playing);
		currentTime = 0;

		// 화면에 있는 ready ui 를 제거 하고 싶다.
		if (readyUI)
		{
			readyUI->RemoveFromViewport();
		}
		// Start UI 가 화면에 보여지게 하자
		if (startUI)
		{
			startUI->AddToViewport();
		}
	}
}
// Start 텍스트 표현하기
// Start 텍스트는 2초후 사라진다.
// 게임 동작하게 한다.
void ACPP_ShootingGameModeBase::PlayingPage()
{
	// 1. 시간이 흐른다.
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 만약 경과시간이 start ui 시간을 초과 했다면
	if (currentTime > startUITime)
	{
		playingStateDelegate.ExecuteIfBound(0);
		
	}
}
// Gameover 메뉴표현하기
// R 키를 누르면 다시 시작 시키기
void ACPP_ShootingGameModeBase::GameoverPage()
{
	// R 키를 입력 받기
	// 1. PlayerController 가져오기
	APlayerController* myController = GetWorld()->GetFirstPlayerController();
	//APlayerController* myController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 2. 키입력 처리 -> R키를 눌렀다면
	// myController 가 있고 R 키를 눌렀다면
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
	// 2. 탄창에 총알을 넣는다.
	bulletPool.AddUnique(bullet);

	if (bTest)
	{
		PRINTLOG(TEXT("Count : %d"), bulletPool.Num());
	}

	// 3. 총알을 비활성화 시킨다.
	SetBulletActive(bullet, false);
}

ABullet* ACPP_ShootingGameModeBase::GetBullet()
{
	// 탄창에서 총알을 하나 빼오고 싶다.
	/*
	for (int32 i = 0;i<bulletPoolSize;++i)
	{
		// 안보인다. -> 비활성화
		if (bulletPool[i]->IsHidden())
		{
			ABullet* bullet = bulletPool[i];
			bulletPool.RemoveAt(0);
			return bullet;
		}
	}*/
	/*
	// 배열에 값이 하나 미만이라면 null 을 반환
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}

	// 1. 풀에서 총알을 하나 빼오기
	ABullet* bullet = bulletPool[0];
	// 2. 탄창에서 빼온 총알 없애기
	bulletPool.RemoveAt(0);
	// -> RemoveAt
	// 3. 총알을 반환해주기
	return bullet;
	*/
	// 풀에 총알이 없다면 null 리턴
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

void ACPP_ShootingGameModeBase::SetState(EGameState s)
{
	mState = s;
	FTimerHandle readyTimer;
	switch (mState)
	{
	case EGameState::Ready:
		// 타이머를 동작시킨다.
		GetWorld()->GetTimerManager().SetTimer(readyTimer, this, &ACPP_ShootingGameModeBase::ReadyPage, readyDelayTime, false, readyDelayTime);
	break;
	case EGameState::Playing:
		break;
	case EGameState::Gameover:
		// 게임 일시 정지
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		// 마우스커서 보이도록 한다.
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

		gameoverUI->AddToViewport();
		break;
	}

}

ABullet* ACPP_ShootingGameModeBase::CreateBullet()
{	
	// 1. 총알공장에서 총알을 만든다.
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	return bullet;
}

void ACPP_ShootingGameModeBase::SetCurrentScore(int32 point)
{
	// 현재 접수 세팅
	curScore = point;
	// UI 에 표시하고 싶다.	
	// scoreui 의 ui widget 에 값을 할당하고 싶다.
	scoreUI->PrintCurrentScore(curScore);

	// top score 는 언제 갱신이 될까??
	// 현재 점수가 최고 점수를 넘어서면
	if (curScore > topScore)
	{
		// 현재점수가 최고점수가 된다.
		topScore = curScore;
		// topScore ui 갱신
		scoreUI->PrintTopScore(topScore);
		
		saveData->topScore = topScore;

		// 데이터를 저장해야 한다.
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"), 0);
	}
}

int32 ACPP_ShootingGameModeBase::GetCurrentScore()
{
	return curScore;
}
