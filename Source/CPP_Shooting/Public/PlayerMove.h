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

	// ����� �Է�ó�� ����� �Լ� �ݹ�
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// �¿� �Է°� ó�� �Լ� ����
	// Axis �Է��� ó���� �Լ��� ���� void �Լ��̸�(float);
	void InputHorizontal(float value);
	// ���� �Է°� ó�� �Լ� ����
	void InputVertical(float value);

	// �¿� �Է��� �޾��� �� �ش� �������� �̵��ϰ� �ʹ�.
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float v = 0;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float speed = 500;

	// �����ϰ� �ִ� Actor ��ü
	UPROPERTY()
	class APlayerCPP* me;
};
