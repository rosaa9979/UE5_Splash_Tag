// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Network/ServerTestGameState.h"
#include "MainMapGameMode.generated.h"

/**
 * 
 */


UCLASS()
class TEAMPROJECT_API AMainMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddPlayerStartPosition(const FVector & Position) { PlayerStartPositionArr.Add(Position); }
	void SetBlackBoardViewCamera(class ABlackBoardViewCameraActor * CameraActor) { BlackBoardViewCamera = CameraActor; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Setting")
	int32 MaxNumOfPlayers = 8;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "System")
	AServerTestGameState* GameState_Ref;

	UPROPERTY(EditDefaultsOnly, Category = "System")
	TArray<AActor*> PlayerStateArray;

	UPROPERTY(EditDefaultsOnly, Category = "System")
	TArray<AController*> GameControllersArray;

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void AddPlayerToArray(AActor* PlayerState, AController* PlayerController);

private:
	TArray<FVector> PlayerStartPositionArr; 

	UPROPERTY()
	class ABlackBoardViewCameraActor * BlackBoardViewCamera;
};
