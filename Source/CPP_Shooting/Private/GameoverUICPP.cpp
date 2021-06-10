// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_Shooting.h"
#include <Components/Button.h>


void UGameoverUICPP::NativeConstruct()
{
	//// UMG�� ��ϵ� UI widget ã�Ƽ� �������� �ʹ�
	//auto restart = Cast<UButton>(GetWidgetFromName(TEXT("Button_Restart")));
	//auto quit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	// ���� auto�� �ڵ����� UButton*�� ��ȯ�� ��
	// ���� �� �����Դٸ�
	if (Button_Restart)
	{
		// -> Click �̺�Ʈ�� �Ҵ��ϰ� �ʹ�.
		Button_Restart->OnClicked.AddDynamic(this, &UGameoverUICPP::OnRestartClicked);
	}
	if (Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &UGameoverUICPP::OnQuitClicked);

	}
}

void UGameoverUICPP::OnRestartClicked()
{
	Restart();
}

void UGameoverUICPP::OnQuitClicked()
{
	Quit();
}

void UGameoverUICPP::Restart()
{
	// ������ �����
	UGameplayStatics::OpenLevel(this, TEXT("Shooting"));
	// gameoverui -> removefromviewport
}

void UGameoverUICPP::Quit()
{
	// ������ �����Ѵ�
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

