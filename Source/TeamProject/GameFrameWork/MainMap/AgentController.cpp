// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/MainMap/AgentController.h"

void AAgentController::BeginPlay()
{
	Super::BeginPlay();

	InitInputMode();
}

void AAgentController::InitInputMode()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
