// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <Components/ArrowComponent.h>
#include <Bullet.h>
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerMove.h"
#include "PlayerFire.h"


// Sets default values
APlayerCPP::APlayerCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// BoxComponent 추가하기
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// BoxComponent 를 루트컴포넌트로 설정
	RootComponent = boxComp;

	// StaticMeshComponent 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// 루트의 자식으로 등록하자
	meshComp->SetupAttachment(boxComp);
	// 충돌 없도록 설정
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Arrowcomponent 추가
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(boxComp);
	firePosition->SetRelativeLocation(FVector(0, 0, 10));

	firePosition2 = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition2"));
	firePosition2->SetupAttachment(boxComp);

	// StaticMesh 데이터 동적으로 로드해서 할당하기
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// 애셋을 성공적으로 로드 했다면 true 를 리턴
	if (TempMesh.Succeeded())
	{
		// 읽어들인 데이터를 할당
		meshComp->SetStaticMesh(TempMesh.Object);
	}
	// 재질 로드하기
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// 애셋을 성공적으로 로드 했다면 true 를 리턴
	if (TempMat.Succeeded())
	{
		// 읽어들인 데이터를 할당
		meshComp->SetMaterial(0, TempMat.Object);
	}

	// PlayerMove 컴포넌트 추가하기
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
	playerFire = CreateDefaultSubobject<UPlayerFire>(TEXT("PlayerFire"));
}

// Called when the game starts or when spawned
void APlayerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
// 사용자가 정의해놓은 입력 값과 처리할 함수를 묶어주는 역할
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);
	playerFire->SetupPlayerInputComponent(PlayerInputComponent);
}

