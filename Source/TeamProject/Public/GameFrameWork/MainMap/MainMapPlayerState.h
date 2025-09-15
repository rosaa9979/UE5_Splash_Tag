// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainMapPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AMainMapPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetTagger() { IsTagger = true;}
	void InitState();	
	FORCEINLINE bool IsPlayerTargger() const { return IsTagger;}

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UPROPERTY(Replicated)
	int ServerNumberID;

	UPROPERTY(Replicated)
	FString PlayerNickName;
	
private:
	bool IsTagger = false;	
};
