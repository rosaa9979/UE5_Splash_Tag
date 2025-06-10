#include "GameFrameWork/MainMap/BlackBoardWidgetActor/BlackBoardWidgetActor.h"

#include "Components/Widget.h"
#include "Components/WidgetComponent.h"

ABlackBoardWidgetActor::ABlackBoardWidgetActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BlackBoardWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BLACKBOARDWIDGET"));
	RootComponent = BlackBoardWidgetComponent;
}

void ABlackBoardWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
}