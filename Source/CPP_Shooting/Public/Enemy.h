// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// Ÿ���� ���� �̵��ϰ� �ʹ�.
// �ʿ�Ӽ� : Ÿ��
UCLASS()
class CPP_SHOOTING_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float speed = 500;

	// �ʿ�Ӽ� : Ÿ��
	UPROPERTY(VisibleAnywhere, Category="Target")
	class AActor* target;

	UPROPERTY(BlueprintReadOnly, Category="Stat")
	FVector dir = FVector(0, 0, 0);

	// ����ȿ�� �Ӽ�
	UPROPERTY(EditDefaultsOnly, Category="Setting")
	class UParticleSystem* explosionFactory;

	// ���� ����
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

	// �浹 �̺�Ʈ ó�� �Լ�
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category="Code")
	void OnCollisionEnter(AActor* OtherActor);
};
