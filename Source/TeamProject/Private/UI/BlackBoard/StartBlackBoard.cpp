// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BlackBoard/StartBlackBoard.h"
#include "Components/Button.h"

void UStartBlackBoard::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Start)
		Btn_Start->OnClicked.AddDynamic(this,&UStartBlackBoard::ClickStartButton);
}

void UStartBlackBoard::ClickStartButton()
{
	UE_LOG(LogTemp,Warning,TEXT("StartButton"));

	int a = 10;
}
