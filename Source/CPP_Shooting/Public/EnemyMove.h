// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UEnemyMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float speed = 500;

	// 필요속성 : 타겟
	UPROPERTY(VisibleAnywhere, Category = "Target")
	class AActor* target;

	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	FVector dir = FVector(0, 0, 0);

	// 폭발효과 속성
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	class UParticleSystem* explosionFactory;

	// 폭발 사운드
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;


	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Code")
	void OnCollisionEnter(AActor* OtherActor);
};
