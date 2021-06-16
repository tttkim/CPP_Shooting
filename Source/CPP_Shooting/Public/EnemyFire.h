// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UEnemyFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ÃÑ½î´Â ÇÔ¼ö
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<class AEnemyBullet> bulletFactory;

	UPROPERTY()
	class AEnemy* me;
};
