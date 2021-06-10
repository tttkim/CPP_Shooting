// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/InputComponent.h>
#include <Components/ArrowComponent.h>
#include "PlayerFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// �Ѿ� �߻� ó���� �Լ�
	void YogaFire();

	// ������Ʈ�� ���ԵǾ� �ִ� Actor ��ü
	class APlayerCPP* me;

	// �Ѿ� �߻� ����
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;
};
