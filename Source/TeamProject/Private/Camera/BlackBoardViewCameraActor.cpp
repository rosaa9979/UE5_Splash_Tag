// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/BlackBoardViewCameraActor.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"

void ABlackBoardViewCameraActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AMainMapGameMode * MainGameMode = GetWorld()->GetAuthGameMode<AMainMapGameMode>();
		if (MainGameMode)
		{
			
		}
	}
}
