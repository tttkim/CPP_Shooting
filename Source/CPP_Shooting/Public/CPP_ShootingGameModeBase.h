// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include "CPP_ShootingGameModeBase.generated.h"


DECLARE_DELEGATE_OneParam(FPlayingStateDelegate, float value)

// 총알 오브젝트풀을 위한 속성 선언
// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장

// 게임의 상태제어
// -> Ready, Playing, Gameover
// 열거형
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Ready UMETA(DisplayName = "READY_STATE"),
	Playing UMETA(DisplayName = "PLAYING_STATE"),
	Gameover UMETA(DisplayName = "GAMEOVER_STATE")
};


UCLASS()
class CPP_SHOOTING_API ACPP_ShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_ShootingGameModeBase();

	FPlayingStateDelegate playingStateDelegate;

	UFUNCTION()
	void PlayingProcess(float value);

	// 게임이 초기화 될 때 호출됨.
	virtual void InitGameState() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ReadyPage();
	void PlayingPage();
	void GameoverPage();

	// 총알 활성화시키는 함수
	void SetBulletActive(ABullet* bullet, bool isActive);
	
	// 탄창에 총알을 추가해주는 함수
	void AddBullet(ABullet* bullet, bool bTest = false);

	// 탄창(풀)에서 총알을 하나 빼오기
	ABullet* GetBullet();

	// BP 에서 함수를 구현하도록 설정하는 옵션
	//UFUNCTION(BlueprintImplementableEvent, Category="PrintLog")
	// BP 에 없으면 C++ 에 있는 함수를 사용하겠다라는 의미
	// -> 단, 소스코드에서 함수는 이름_Implementation 으로 해주어야 한다.
	UFUNCTION(BlueprintNativeEvent, Category="PrintLog")
	void PrintEnumData(EGameState value);

	EGameState GetState()
	{
		return mState;
	}

	// 상태 바꾸는 함수
	void SetState(EGameState s);

private:
	ABullet* CreateBullet();

	// 상태변수
	// -> Blueprint 에 속성(변수) 노출시키고 싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta=(AllowPrivateAccess = true))
	EGameState mState = EGameState::Ready;	

	// 필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장
	UPROPERTY(EditDefaultsOnly, Category = "Bullet", meta = (AllowPrivateAccess = true))
	int bulletPoolSize;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", meta = (AllowPrivateAccess = true))
	TArray<ABullet*> bulletPool;

	// 공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ABullet> bulletFactory;

	// 필요속성 : (대기시간)일정시간, 경과시간
	UPROPERTY(EditAnywhere, Category="State", meta = (AllowPrivateAccess = true))
	float readyDelayTime = 2;

	UPROPERTY()
	float currentTime = 0;

	// Ready Widget BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta=(AllowPrivateAccess=true))
	TSubclassOf<class UUserWidget> readyUIFactory;

	// ready ui 를 재활용 하기 위해 속성으로 등록해 놓고 사용하자.
	UPROPERTY()
	class UUserWidget* readyUI;

	// Start Widget BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> startUIFactory;

	// Start ui 를 재활용 하기 위해 속성으로 등록해 놓고 사용하자.
	UPROPERTY()
	class UUserWidget* startUI;

	// Gameover Widget BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> gameoverUIFactory;

	// gameover ui 를 재활용 하기 위해 속성으로 등록해 놓고 사용하자.
	UPROPERTY()
	class UUserWidget* gameoverUI;

	UPROPERTY(EditAnywhere, Category="UI", meta = (AllowPrivateAccess = true))
	float startUITime = 1.5f;

	// 현재점수
	int32 curScore = 0;
	// 최고점수
	int32 topScore = 0;

	// UserWidget -> ScoreUI
	UPROPERTY(EditDefaultsOnly, Category="UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> scoreUIFactory;

	// scoreui 공장에서 만들어진 scoreui 를 기억할 변수
	UPROPERTY()
	class UScoreUI* scoreUI;

	// SaveGame 인스턴스를 변수로 기억
	UPROPERTY()
	class USaveData* saveData;

public:
	void SetCurrentScore(int32 point);
	int32 GetCurrentScore();
};
