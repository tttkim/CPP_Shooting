// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// 이동속도
	UPROPERTY(EditAnywhere, Category = "Stat")
	float speed = 700;
	

	// Sets default values for this actor's properties
	AEnemyBullet();

	// 폭발효과 속성
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	class UParticleSystem* explosionFactory;

	// 폭발 사운드
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
