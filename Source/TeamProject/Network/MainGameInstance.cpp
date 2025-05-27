#include "MainGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UMainGameInstance::UMainGameInstance()
	: CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
	,FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this,&ThisClass::OnFindSessionComplete))
	,JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this,&ThisClass::OnJoinSessionComplete))
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	}
}

void UMainGameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())
		return;

	//해당 이름을 가진 세션이 이미 존재하면 파괴
	auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
	}

	//CreateSession이 성공시 호출할 Delegate를 DelegateList에 추가
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	//Create Session Setting Object
	//-----------------------------------------------
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = false;			//랜 연결을 할지 정하는 변수
	SessionSettings->NumPublicConnections = 4;		//연결할 유저 수
	SessionSettings->bAllowJoinInProgress = true;	//게임 세션 실행중이면 다른유저도 가입 가능한지
	SessionSettings->bAllowJoinViaPresence = true;	//친구	리스트에서 Join?
	SessionSettings->bShouldAdvertise = true;		//세션 광고
	SessionSettings->bUseLobbiesIfAvailable = true;	//로비 시스템
	SessionSettings->Set(FName("MatchType"), FString("Mission"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	//첫번째 인자는 세션의 유형, 두번째 인자는 게임의 방식
	//-----------------------------------------------

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void UMainGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 15.f, FColor::Red, FString::Printf(TEXT("Complete Create")));
	}

	//CreateSesison 성공시 Lobby맵 ListemServer로 오픈
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
			World->ServerTravel(FString("/Game/_GamePlay/Map/MainMap?listen"));
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 15.f, FColor::Red, FString::Printf(TEXT("Failed to Create Session")));
		}
	}
}

void UMainGameInstance::JoinGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));
		return;
	}

	//Session찾으면 호출할 Delegate등록
	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void UMainGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!OnlineSessionInterface.IsValid())
		return;

	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Connect String : %s"), *Address));

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UMainGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (!OnlineSessionInterface.IsValid() || !bWasSuccessful)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Failed")));
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 15.f, FColor::Red, FString::Printf(TEXT("%d"), SessionSearch->SearchResults.Num()));
	}


	for (auto Result : SessionSearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;

		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);


		UE_LOG(LogTemp, Warning, TEXT("%s AFEFEFE"), *MatchType);

		if (MatchType == FString("Mission"))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining Match Type : %s"), *MatchType));

			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}
