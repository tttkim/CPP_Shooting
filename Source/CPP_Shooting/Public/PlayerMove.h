// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/InputComponent.h>
#include "PlayerMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 사용자 입력처리 담당할 함수 콜백
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// 좌우 입력값 처리 함수 선언
	// Axis 입력을 처리할 함수의 원형 void 함수이름(float);
	void InputHorizontal(float value);
	// 상하 입력값 처리 함수 선언
	void InputVertical(float value);

	// 좌우 입력을 받았을 때 해당 방향으로 이동하고 싶다.
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float v = 0;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float speed = 500;

	// 소유하고 있는 Actor 객체
	UPROPERTY()
	class APlayerCPP* me;
};
