// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"
#include <Components/InputComponent.h>
#include <Components/ArrowComponent.h>

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());

}


// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// gamemode 의 상태가 playing 이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	// 오른쪽으로 이동시켜보자
	// P = P0 + vt
	// RightVector -> (x, y, z) (0, 1, 0)
	//FVector v(0, 1, 0);
	//FVector v = FVector(0, 1, 1);
	// 1. 방향이 필요하다.
	FVector vel = FVector(0, h, v);
	vel.Normalize();
	//v = v * 500;
	vel *= speed;

	FVector P0 = me->GetActorLocation();
	FVector P = P0 + vel * DeltaTime;
	// 2. 위치를 지정하고 싶다. -> 이동하고싶다.
	me->SetActorLocation(P);
	// Yaw 축으로 회전하고 싶다.
	// R = R0 + rt
	/*FRotator R0 = GetActorRotation();
	FRotator r = FRotator(0, 1, 0) * 100;
	FRotator R = R0 + r * DeltaTime;
	SetActorRotation(R);*/
}

void UPlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMove::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMove::InputVertical);
}

// 사용자의 Horizontal 입력 처리할 함수
void UPlayerMove::InputHorizontal(float value)
{
	h = value;
}

void UPlayerMove::InputVertical(float value)
{
	v = value;
}