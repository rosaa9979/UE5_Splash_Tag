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
