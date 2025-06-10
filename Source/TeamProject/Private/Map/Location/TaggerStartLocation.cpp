#include "Map/Location/TaggerStartLocation.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"

ATaggerStartLocation::ATaggerStartLocation()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATaggerStartLocation::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AMainMapGameMode * GameMode = GetWorld()->GetAuthGameMode<AMainMapGameMode>())
		{
			GameMode->AddTaggerInitLocation(GetActorLocation());
		}
	}
}


