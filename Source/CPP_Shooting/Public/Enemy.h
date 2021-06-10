// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// 타겟을 따라서 이동하고 싶다.
// 필요속성 : 타겟
UCLASS()
class CPP_SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float speed = 500;

	// 필요속성 : 타겟
	UPROPERTY(VisibleAnywhere, Category="Target")
	class AActor* target;

	UPROPERTY(BlueprintReadOnly, Category="Stat")
	FVector dir = FVector(0, 0, 0);

	// 폭발효과 속성
	UPROPERTY(EditDefaultsOnly, Category="Setting")
	class UParticleSystem* explosionFactory;

	// 폭발 사운드
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌 이벤트 처리 함수
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category="Code")
	void OnCollisionEnter(AActor* OtherActor);
};
