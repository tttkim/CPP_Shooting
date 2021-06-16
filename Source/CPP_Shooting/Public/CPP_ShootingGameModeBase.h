// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include "CPP_ShootingGameModeBase.generated.h"


DECLARE_DELEGATE_OneParam(FPlayingStateDelegate, float value)

// �Ѿ� ������ƮǮ�� ���� �Ӽ� ����
// �ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���

// ������ ��������
// -> Ready, Playing, Gameover
// ������
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

	// ������ �ʱ�ȭ �� �� ȣ���.
	virtual void InitGameState() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ReadyPage();
	void PlayingPage();
	void GameoverPage();

	// �Ѿ� Ȱ��ȭ��Ű�� �Լ�
	void SetBulletActive(ABullet* bullet, bool isActive);
	
	// źâ�� �Ѿ��� �߰����ִ� �Լ�
	void AddBullet(ABullet* bullet, bool bTest = false);

	// źâ(Ǯ)���� �Ѿ��� �ϳ� ������
	ABullet* GetBullet();

	// BP ���� �Լ��� �����ϵ��� �����ϴ� �ɼ�
	//UFUNCTION(BlueprintImplementableEvent, Category="PrintLog")
	// BP �� ������ C++ �� �ִ� �Լ��� ����ϰڴٶ�� �ǹ�
	// -> ��, �ҽ��ڵ忡�� �Լ��� �̸�_Implementation ���� ���־�� �Ѵ�.
	UFUNCTION(BlueprintNativeEvent, Category="PrintLog")
	void PrintEnumData(EGameState value);

	EGameState GetState()
	{
		return mState;
	}

	// ���� �ٲٴ� �Լ�
	void SetState(EGameState s);

private:
	ABullet* CreateBullet();

	// ���º���
	// -> Blueprint �� �Ӽ�(����) �����Ű�� �ʹ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta=(AllowPrivateAccess = true))
	EGameState mState = EGameState::Ready;	

	// �ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category = "Bullet", meta = (AllowPrivateAccess = true))
	int bulletPoolSize;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", meta = (AllowPrivateAccess = true))
	TArray<ABullet*> bulletPool;

	// ����
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ABullet> bulletFactory;

	// �ʿ�Ӽ� : (���ð�)�����ð�, ����ð�
	UPROPERTY(EditAnywhere, Category="State", meta = (AllowPrivateAccess = true))
	float readyDelayTime = 2;

	UPROPERTY()
	float currentTime = 0;

	// Ready Widget BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta=(AllowPrivateAccess=true))
	TSubclassOf<class UUserWidget> readyUIFactory;

	// ready ui �� ��Ȱ�� �ϱ� ���� �Ӽ����� ����� ���� �������.
	UPROPERTY()
	class UUserWidget* readyUI;

	// Start Widget BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> startUIFactory;

	// Start ui �� ��Ȱ�� �ϱ� ���� �Ӽ����� ����� ���� �������.
	UPROPERTY()
	class UUserWidget* startUI;

	// Gameover Widget BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> gameoverUIFactory;

	// gameover ui �� ��Ȱ�� �ϱ� ���� �Ӽ����� ����� ���� �������.
	UPROPERTY()
	class UUserWidget* gameoverUI;

	UPROPERTY(EditAnywhere, Category="UI", meta = (AllowPrivateAccess = true))
	float startUITime = 1.5f;

	// ��������
	int32 curScore = 0;
	// �ְ�����
	int32 topScore = 0;

	// UserWidget -> ScoreUI
	UPROPERTY(EditDefaultsOnly, Category="UI", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> scoreUIFactory;

	// scoreui ���忡�� ������� scoreui �� ����� ����
	UPROPERTY()
	class UScoreUI* scoreUI;

	// SaveGame �ν��Ͻ��� ������ ���
	UPROPERTY()
	class USaveData* saveData;

public:
	void SetCurrentScore(int32 point);
	int32 GetCurrentScore();
};
