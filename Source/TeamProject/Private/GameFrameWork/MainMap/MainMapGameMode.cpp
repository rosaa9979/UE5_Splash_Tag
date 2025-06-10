#include "GameFrameWork/MainMap/MainMapGameMode.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/MainMap/MainMapPlayerState.h"
#include "GameFrameWork/MainMap/MainMapGameState.h"
#include "Kismet/GameplayStatics.h"

void AMainMapGameMode::GameStart()
{
	//술래 정하기
	//----------------------------------------------------
	TArray<int32> TaggerIndexArr;
	TaggerIndexArr.Init(0,TaggerNum);
	TaggerIndexArr[0] = FMath::RandRange(0, MaxNumOfPlayers - 1);
	// int32 OtherIndex = FMath::RandRange(0, TaggerNum - 1);
	// while (OtherIndex == TaggerIndexArr[0] )
	// {
	// 	OtherIndex = FMath::RandRange(0, TaggerNum - 1);
	// }
	// TaggerIndexArr[1] = OtherIndex;
	//----------------------------------------------------

	for (int32 idx = 0; idx <  MaxNumOfPlayers; ++idx)
	{
		FVector SpawnLocation;
		if (idx == TaggerIndexArr[0])
		{
			MainMapPlayerStateArr[idx]->SetTagger();
			SpawnLocation = TaggerInitLocationArr[0];
		}
		// else if (idx == TaggerIndexArr[1])
		// {
		// 	PlayerStateArray[idx]->SetTagger();
		// 	SpawnLocation = TaggerInitLocationArr[0];
		// }
		else
			SpawnLocation = PlayerStartPositionArr[idx];
		
		if (ACharacter * CurCharacter = GameControllersArray[idx]->GetCharacter())
			CurCharacter->SetActorLocation(SpawnLocation);
	}

	MainMapGameState->SetRemainSecond(GameProgressTime);
}

void AMainMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp,Warning,TEXT("GameModeBeginPlay"));

	MainMapGameState = Cast<AMainMapGameState>(UGameplayStatics::GetGameState(this));
}

void AMainMapGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp,Warning,TEXT("GameModePostLogin"));
	
	if (GameControllersArray.Num() < MaxNumOfPlayers)
	{
		AMainMapPlayerState* NewPlayerState = Cast<AMainMapPlayerState>(NewPlayer->PlayerState);

		AddPlayerToArray(NewPlayerState, NewPlayer);
	}
}

void AMainMapGameMode::AddPlayerToArray(AMainMapPlayerState* PlayerState, AController* PlayerController)
{
	MainMapPlayerStateArr.AddUnique(PlayerState);
	GameControllersArray.AddUnique(PlayerController);
}
