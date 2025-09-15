#include "GameFrameWork/MainMap/BlackBoardViewTrigger/BlackBoardViewTrigger.h"
#include "GameFrameWork/MainMap/MainMapPlayerController.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"
#include "GameFrameWork/MainMap/MainMapGameState.h"
#include "Camera/BlackBoardViewCameraActor.h"
#include "Components/BoxComponent.h"
#include "Player/Character/RunnerCharacter.h"


ABlackBoardViewTrigger::ABlackBoardViewTrigger()
	: IsStartUITrigger(false)
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	if (IsStartUITrigger)
	{
		if (HasAuthority())
		{
			TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap); // 캐릭터만 감지
		}
	}
	else
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap); // 캐릭터만 감지
	}
}

void ABlackBoardViewTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainMapGameState * GameState = GetWorld()->GetGameState<AMainMapGameState>();
	if (nullptr == GameState || GameState->GetCurrentGameState() == EGameState::Playing)
		return;	

	if (IsStartUITrigger && !HasAuthority())
		return;
	
	ARunnerCharacter * Runner = Cast<ARunnerCharacter>(OtherActor);
	if (nullptr == Runner)
		return;
	
	if (Runner->IsLocallyControlled())
	{
		if (AMainMapPlayerController * PlayerController = Cast<AMainMapPlayerController>(Runner->GetController()))
		{
			PlayerController->SetVisibleMainHUD(false);
			
			if (TriggerCamera)
			{
				PlayerController->SetViewTargetWithBlend(TriggerCamera,1.0f);
			}
			
			if (IsStartUITrigger)
			{
				FInputModeGameAndUI InputMode = FInputModeGameAndUI();
				InputMode.SetHideCursorDuringCapture(false);				
				PlayerController->SetInputMode(InputMode);
				//PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->SetShowMouseCursor(true);
				PlayerController->SetVisibleBlackBoard(true);
			}			
		}
	}
}

void ABlackBoardViewTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainMapGameState * GameState = GetWorld()->GetGameState<AMainMapGameState>();
	if (nullptr == GameState || GameState->GetCurrentGameState() == EGameState::Playing)
		return;
	
	if (IsStartUITrigger && !HasAuthority())
		return;

	ARunnerCharacter * Runner = Cast<ARunnerCharacter>(OtherActor);
	if (nullptr == Runner)
		return;
	
	if (Runner->IsLocallyControlled())
	{
		if (AMainMapPlayerController * PlayerController = Cast<AMainMapPlayerController>(Runner->GetController()))
		{
			PlayerController->SetVisibleMainHUD(true);
			PlayerController->SetViewTargetWithBlend(Runner,1.0f);
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetVisibleBlackBoard(false);
		}
	}
}

void ABlackBoardViewTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABlackBoardViewTrigger::BeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABlackBoardViewTrigger::EndOverlap);
	
}
