// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "StudentPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AStudentPlayerStart : public APlayerStart
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
	
};
