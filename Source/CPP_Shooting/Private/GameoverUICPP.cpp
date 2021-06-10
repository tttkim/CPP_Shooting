// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_Shooting.h"
#include <Components/Button.h>


void UGameoverUICPP::NativeConstruct()
{
	//// UMG에 등록된 UI widget 찾아서 가져오고 싶다
	//auto restart = Cast<UButton>(GetWidgetFromName(TEXT("Button_Restart")));
	//auto quit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	// 위의 auto는 자동으로 UButton*로 변환될 것
	// 만약 잘 가져왔다면
	if (Button_Restart)
	{
		// -> Click 이벤트를 할당하고 싶다.
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
	// 레벨을 재시작
	UGameplayStatics::OpenLevel(this, TEXT("Shooting"));
	// gameoverui -> removefromviewport
}

void UGameoverUICPP::Quit()
{
	// 게임을 종료한다
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

