// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/MainMap/MainMapGameState.h"
#include "GameFrameWork/MainMap/MainMapPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AMainMapGameState::AMainMapGameState()
	: RemainSecond(0)
{
	
}

void AMainMapGameState::SetRemainSecond(int Second)
{
	RemainSecond = Second;

	UpdateRemainUI();
}

void AMainMapGameState::OnRep_RemainSecond()
{
	if(AMainMapPlayerController * LocalController =
		Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
	{
		LocalController->UpdateRemainTime(RemainSecond);
	}
}

void AMainMapGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMapGameState, RemainSecond);
}

void AMainMapGameState::UpdateRemainUI()
{
	UE_LOG(LogTemp,Warning,TEXT("GameState"));
}
