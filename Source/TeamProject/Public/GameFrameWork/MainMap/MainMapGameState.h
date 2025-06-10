// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainMapGameState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AMainMapGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMainMapGameState();

public:
	void SetRemainSecond(int Second);	//Second 갱신하면서 UI도 Update

	UFUNCTION()
	void OnRep_RemainSecond();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	void UpdateRemainUI();
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_RemainSecond)
	int RemainSecond;
};
