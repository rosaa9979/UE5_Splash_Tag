// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AgentController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AAgentController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	void InitInputMode();
};
