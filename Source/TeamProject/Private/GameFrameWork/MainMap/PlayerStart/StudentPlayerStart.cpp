// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/MainMap/PlayerStart/StudentPlayerStart.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"

void AStudentPlayerStart::BeginPlay()
{
	Super::BeginPlay();

	//GameMode에 위치 저장
	if (HasAuthority())
	{
		AMainMapGameMode * MainGameMode = GetWorld()->GetAuthGameMode<AMainMapGameMode>();
		if (MainGameMode)
		{
			MainGameMode->AddPlayerStartPosition(GetActorLocation());
		}
	}
}
