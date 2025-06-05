// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Logging/LogMacros.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SteamSessionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API USteamSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void CreateGameSession();

	void JoinGameSession();

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnFindSessionsComplete(bool bWasSuccessful);


	IOnlineSessionPtr OnlineSessionInterface;

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	//SessionList
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
