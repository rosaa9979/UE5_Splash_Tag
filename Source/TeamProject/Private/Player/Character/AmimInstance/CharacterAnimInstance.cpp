// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Character/AmimInstance/CharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Character/BaseCharacter.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	// GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	//
	bHasAccelerationCode = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	//
	// LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	//
	// Pitch = OwningCharacter->GetBaseAimRotation().Pitch;
	

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(OwningCharacter))
	{
		bIsCrouching = Character->bIsRunnerCrouch;
		bIsTaggerCrouching = Character->bIsTaggerCrouch;
	}

	// Runner State
	bIsAiming = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Runner.Status.Aiming"));
	bIsSprinting = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Runner.Status.Running"));
	bIsUsing = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Runner.Status.Using"));
	bIsEquipping = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Runner.Status.Equipping"));
	bIsUnEquipping = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Runner.Status.UnEquipping"));

	// Tagger State
	bIsTaggerRunning = OwnerHasTag(FGameplayTag::RequestGameplayTag("Player.Tagger.Status.Running"));

	
}
