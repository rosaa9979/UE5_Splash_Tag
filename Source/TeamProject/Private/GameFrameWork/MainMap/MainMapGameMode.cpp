#include "GameFrameWork/MainMap/MainMapGameMode.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void AMainMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameState_Ref = Cast<AServerTestGameState>(UGameplayStatics::GetGameState(this));
}

void AMainMapGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp,Warning,TEXT("GameModePostLogin"));
	
	if (GameControllersArray.Num() < MaxNumOfPlayers)
	{
		AActor* NewPlayerState = Cast<AActor>(NewPlayer->PlayerState);

		AddPlayerToArray(NewPlayerState, NewPlayer);
	}
}

void AMainMapGameMode::AddPlayerToArray(AActor* PlayerState, AController* PlayerController)
{
	PlayerStateArray.AddUnique(PlayerState);
	GameControllersArray.AddUnique(PlayerController);
}
