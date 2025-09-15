// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/AbilitySystem/Abilities/RunnerGameplayAbility.h"

#include "GameFrameWork/MainMap/MainMapGameMode.h"
#include "GameFrameWork/MainMap/MainMapPlayerController.h"
#include "Player/Character/RunnerCharacter.h"

ARunnerCharacter* URunnerGameplayAbility::GetRunnerCharacterFromActorInfo()
{
	if (!CachedRunnerCharacter.IsValid())
	{
		CachedRunnerCharacter = Cast<ARunnerCharacter>(CurrentActorInfo->AvatarActor);
		
	}

	return CachedRunnerCharacter.IsValid() ? CachedRunnerCharacter.Get() : nullptr;
}

AMainMapPlayerController* URunnerGameplayAbility::GetMainMapPlayerControllerFromRunnerInfo()
{
	if (!CachedMainMapPlayerController.IsValid())
	{
		CachedMainMapPlayerController = Cast<AMainMapPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedMainMapPlayerController.IsValid() ? CachedMainMapPlayerController.Get() : nullptr;
}

URunnerRepelComponent* URunnerGameplayAbility::GetRunnerRepelComponentFromRunnerInfo()
{
	return GetRunnerCharacterFromActorInfo()->GetRunnerRepelComponent();
}

URunnerInterActiveComponent* URunnerGameplayAbility::GetRunnerInterActiveComponent()
{
	return GetRunnerCharacterFromActorInfo()->GetRunnerInterActiveComponent();
}

AMainMapGameMode* URunnerGameplayAbility::GetMainMapGameModeFromRunnerInfo()
{
	if (UWorld* World = CurrentActorInfo ? CurrentActorInfo->AvatarActor->GetWorld() : nullptr)
	{
		CachedMainMapGameMode = Cast<AMainMapGameMode>(World->GetAuthGameMode());
	}

	return CachedMainMapGameMode.IsValid() ? CachedMainMapGameMode.Get() : nullptr;
}
