// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BlackBoardViewCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ABlackBoardViewCameraActor : public ACameraActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
	
};
