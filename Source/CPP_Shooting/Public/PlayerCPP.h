// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Pawn.h"
#include "PlayerCPP.generated.h"

// BoxCollider 컴포넌트를 추가하고 싶다.
//사용자가 발사 버튼을 누르면 총알을 발사하고 싶다.
// 필요속성 : 총구위치, 공장
//1. 사용자가 발사 버튼을 눌렀으니까
//2. 총알을 만들어야 한다.
//3. 총알을 위치시킨다.
UCLASS()
class CPP_SHOOTING_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	// 접근권한
	//UPROPERTY(EditAnywhere, EditDefaultsOnly, EditInstanceOnly, VisibleAnywhere, VisibleDefaultsOnly, VisibleInstanceOnly)
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadWrite)

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// 필요속성 : 총구위치, 공장
	UPROPERTY(EditAnywhere, Category = "Component")
	class UArrowComponent* firePosition;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UArrowComponent* firePosition2;

	// PlayerMove 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerMove* playerMove;

	// PlayerFire 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerFire* playerFire;

public:
	// Sets default values for this pawn's properties
	APlayerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
