#include "Network/MainGameInstance.h"
#include "Network/SteamSessionSubsystem.h"

void UMainGameInstance::Init()
{
	Super::Init();

	SessionManager = GetSubsystem<USteamSessionSubsystem>();
}

void UMainGameInstance::CreateGameSession()
{
	if (SessionManager)
	{
		SessionManager->CreateGameSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ListenGameInstanceServer is not initialized."));
	}
}

void UMainGameInstance::JoinGameSession()
{
	if (SessionManager)
	{
		SessionManager->JoinGameSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ListenGameInstanceServer is not initialized."));
	}
}
