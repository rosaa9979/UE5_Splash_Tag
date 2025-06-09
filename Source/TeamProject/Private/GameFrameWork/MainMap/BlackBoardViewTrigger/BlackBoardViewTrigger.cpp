#include "GameFrameWork/MainMap/BlackBoardViewTrigger/BlackBoardViewTrigger.h"
#include "Components/BoxComponent.h"
#include "Player/Agent.h"

ABlackBoardViewTrigger::ABlackBoardViewTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	TriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ABlackBoardViewTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Call"));
	if (HasAuthority())
	{
		AAgent * Agent = Cast<AAgent>(OtherActor);
		if (nullptr == Agent)
			return;
		
		if (Agent->IsLocallyControlled())
		{
			UE_LOG(LogTemp,Warning,TEXT("ServerOverlap"));
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("ClientOverlap"));
		}
	}
}

void ABlackBoardViewTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		
	}
}

void ABlackBoardViewTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABlackBoardViewTrigger::BeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABlackBoardViewTrigger::EndOverlap);
	
}
