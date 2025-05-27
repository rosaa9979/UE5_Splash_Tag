// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Logging/LogMacros.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMainGameInstance();

public:
	void CreateGameSession();
	void JoinGameSession();

private:
	//Session생성 성공시 Delegate 함수
	//---------------------------------------
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	//CreateSession성공 시 호출 함수
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	//---------------------------------------


	//Session참가 성공시 Delegate 함수
	//---------------------------------------
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	//---------------------------------------

	//Session찾기 성공시 Delegate 함수
	//---------------------------------------
	void OnFindSessionComplete(bool bWasSuccessful);

	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	//---------------------------------------

	IOnlineSessionPtr OnlineSessionInterface;

private:
	//SessionList
	TSharedPtr<FOnlineSessionSearch> SessionSearch; 
};
