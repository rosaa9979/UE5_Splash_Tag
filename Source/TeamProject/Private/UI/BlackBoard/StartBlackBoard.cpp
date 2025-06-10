// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BlackBoard/StartBlackBoard.h"
#include "Components/Button.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"

void UStartBlackBoard::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Start)
		Btn_Start->OnClicked.AddDynamic(this,&UStartBlackBoard::ClickStartButton);
}

void UStartBlackBoard::ClickStartButton()
{
	if (GetOwningPlayer() && GetOwningPlayer()->HasAuthority())
	{
		if (AMainMapGameMode * GameMode = GetWorld()->GetAuthGameMode<AMainMapGameMode>())
		{
			GameMode->GameStart();
		}
	}
}
