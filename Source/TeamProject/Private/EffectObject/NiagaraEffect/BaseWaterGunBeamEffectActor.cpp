// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObject/NiagaraEffect/BaseWaterGunBeamEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EffectObject/NiagaraEffect/BaseWaterGunHitEffectActor.h"

#include "NiagaraComponent.h"
#include "ParticleHelper.h"
#include "Camera/CameraComponent.h"
#include "EffectObjectPool/EffectObjectPoolSubSystem.h"
#include "Engine/TargetPoint.h"
#include "GameTag/STGamePlayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/Character/RunnerCharacter.h"
#include "Player/Character/Libraries/STFunctionLibrary.h"


FOnSplashHIt ABaseWaterGunBeamEffectActor::OnSplashHit;

ABaseWaterGunBeamEffectActor::ABaseWaterGunBeamEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	NiagaraComp->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	NiagaraComp->SetRelativeScale3D(FVector(1.2f));
}

void ABaseWaterGunBeamEffectActor::BeginPlay()
{
	Super::BeginPlay();

	BeamLengthBck = BeamLength;
	
	NiagaraComp->SetVariableFloat("User.size", SizeCorrect);

	SetActorTickEnabled(false);
}

void ABaseWaterGunBeamEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckCollision();

	UpdateBeamPosition();

	CheckDestroy();
}

void ABaseWaterGunBeamEffectActor::CheckDestroy_Implementation()
{
	if ((BeamEndActor->GetActorLocation() - BeamStartActor->GetActorLocation()).Size() <= MeetDistance)
	{
		FinishLoop();
	}

}

void ABaseWaterGunBeamEffectActor::FinishLoop_Implementation()
{
	HitEffectActorInstance->ReturnEffectActor();
	HitEffectActorInstance = nullptr;

	BeamStartActor->Destroy();
	BeamStartActor = nullptr;

	BeamEndActor->Destroy();
	BeamEndActor = nullptr;
	
	SetActorTickEnabled(false);
	ReturnToObjectPool();
}

void ABaseWaterGunBeamEffectActor::EffectSetUp(const ABaseCharacter* Player, const ABaseObject* Object)
{
	SetActorTickEnabled(true);
	
	BeamLength = 0;
	
	NiagaraComp->SetVariableVec3(FName(TEXT("User.beamEnd")), FVector(BeamLengthBck, 0.0f, 0.0f));

	CachedObject = const_cast<ABaseObject*>(Object);
	CachedCharacter = const_cast<ABaseCharacter*>(Player);

	OverlappedActors.Empty();

	const ARunnerCharacter* Runner = Cast<ARunnerCharacter>(Player);
	if (BeamStartActor == nullptr)
		BeamStartActor = GetWorld()->SpawnActor<ATargetPoint>();

	if (IsValid(BeamStartActor))
	{
		BeamStartActor->SetActorLocation(GetActorLocation());
	}

	StartPosition = GetActorLocation();

	if (BeamEndActor == nullptr)
		BeamEndActor = GetWorld()->SpawnActor<ATargetPoint>();

	if (IsValid(BeamEndActor))
	{
		TArray<FHitResult> OutResults;
		FVector ForwardVector = FVector::ZeroVector;
		//FVector ForwardVector = CachedCharacter->GetActorForwardVector();
		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(CachedObject.Get());
		IgnoreActors.Add(CachedCharacter.Get());

		FVector PivotVector;
		FVector PivotForwardVector;
		
		UCameraComponent* RunnerCamera = Runner->FindComponentByClass<UCameraComponent>();
		if (RunnerCamera != nullptr)
		{
			PivotVector = RunnerCamera->GetComponentLocation();
			PivotForwardVector = RunnerCamera->GetForwardVector();
		}
		
		else
		{
			PivotVector = FVector::ZeroVector;
			PivotForwardVector = FVector::ZeroVector;
		}

			
		
		UKismetSystemLibrary::LineTraceMulti(
			GetWorld(),
			PivotVector,
			PivotVector + (PivotForwardVector * 2000.0f),
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			IgnoreActors,  // 빈 배열
			EDrawDebugTrace::None,
			OutResults,
			true
		);

		for (FHitResult& OutResult : OutResults)
		{
			// Actor가 없으면 skip
			if (!OutResult.GetActor())
				continue;
        
			// 뒤쪽이면 skip  
			if (FVector::DotProduct(PivotForwardVector, 
								   OutResult.ImpactPoint - BeamStartActor->GetActorLocation()) < 0.0f)
				continue;

			// 조건을 통과한 첫 번째 결과
			ForwardVector = OutResult.ImpactPoint;
			break;
		}

		if (ForwardVector.IsNearlyZero())
			ForwardVector = PivotVector + (PivotForwardVector * 2000.0f);

		//FVector HorizontalVector = FVector(ForwardVector.X, ForwardVector.Y, 0);
		//BeamDirectionNormal = HorizontalVector.GetSafeNormal();
		BeamDirectionNormal = (ForwardVector - BeamStartActor->GetActorLocation()).GetSafeNormal();
		
		BeamEndActor->SetActorLocation(GetActorLocation() + (BeamLengthBck * BeamDirectionNormal));
	}

	if (HitEffectActorInstance == nullptr)
	{
		HitEffectActorInstance = Cast<ABaseWaterGunHitEffectActor>(GetWorld()->GetSubsystem<UEffectObjectPoolSubSystem>()->GetEffectObject(HitEffectActor));
		//HitEffectActorInstance = GetWorld()->SpawnActor<ABaseWaterGunHitEffectActor>(HitEffectActor);
	}
	
	
	if (HitEffectActorInstance != nullptr)
	{
		SetHitEffectActive(true);
		HitEffectActorInstance->SetEffectActorSize(SizeCorrect * 3);
	}
}

void ABaseWaterGunBeamEffectActor::CheckCollision_Implementation()
{
	FVector StartVector = RootComponent->GetComponentLocation();
	FVector EndVector = StartVector + (UKismetMathLibrary::GetForwardVector(RootComponent->GetComponentRotation()) * (BeamLength));

	if (BeamStartActor)
		StartVector = BeamStartActor->GetActorLocation();
	if (BeamEndActor)
		EndVector = BeamEndActor->GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("Start Vector : %s, End Vector : %s"), *StartVector.ToString(), *EndVector.ToString());

	/*
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = {
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic),
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)
	};
	*/

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = {
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic),
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic),
		UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn),
	};

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(CachedObject.Get());
	IgnoreActors.Add(CachedCharacter.Get());
	FHitResult OutResult;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartVector,
		EndVector,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		OutResult,
		true
	);

	Multicast_ApplyCollision(OutResult);
}

void ABaseWaterGunBeamEffectActor::Multicast_ApplyCollision_Implementation(FHitResult OutResult)
{
	if (HitEffectActorInstance == nullptr)
		return;
	
	if (!OutResult.ImpactPoint.Equals(FVector::ZeroVector, 0.0001))
	{
		if (IsValid(OutResult.GetActor()))
		{
			HitEffectActorInstance->SetActorLocation(OutResult.ImpactPoint);

			BeamEndActor->SetActorLocation(OutResult.ImpactPoint);
			SetHitEffectActive(true);

			FGameplayEventData EventData;
			EventData.Instigator = this;
			EventData.Target = OutResult.GetActor();
			EventData.EventTag = STGamePlayTags::Event_OnSplashHit;

			FGameplayAbilityTargetDataHandle TargetDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(OutResult);
    
			EventData.TargetData = TargetDataHandle;

			if (!OverlappedActors.Contains(OutResult.GetActor()) && Cast<ABaseCharacter>(OutResult.GetActor()))
			{
				OverlappedActors.Add(OutResult.GetActor());
				UAbilitySystemComponent* AbilitySystemComponent = USTFunctionLibrary::NativeGetParentAbilitySystemComponentFromActor(OutResult.GetActor());
				
				if (AbilitySystemComponent != nullptr)
				{
					//AbilitySystemComponent->HandleGameplayEvent(STGamePlayTags::Event_OnSplashHit, &EventData);

					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OutResult.GetActor(), STGamePlayTags::Event_OnSplashHit, EventData);
				}
			}

			else if (!Cast<ABaseCharacter>(OutResult.GetActor()))
			{
				UAbilitySystemComponent* AbilitySystemComponent = USTFunctionLibrary::NativeGetParentAbilitySystemComponentFromActor(OutResult.GetActor());

				if (AbilitySystemComponent)
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OutResult.GetActor(), STGamePlayTags::Event_OnSplashHit, EventData);
			}
		}
		else
		{
			SetHitEffectActive(false);

			BeamEndActor->SetActorLocation(BeamEndActor->GetActorLocation() + (BeamDirectionNormal * GetWorld()->GetDeltaSeconds() * BeamEndMoveSpeed));
		}
	}

	else
	{
		SetHitEffectActive(false);

		BeamEndActor->SetActorLocation(BeamEndActor->GetActorLocation() + (BeamDirectionNormal * GetWorld()->GetDeltaSeconds() * BeamEndMoveSpeed));
	}
}

void ABaseWaterGunBeamEffectActor::BeamControl(float NewBeamLength)
{
	NiagaraComp->SetVariableVec3(FName(TEXT("User.beamEnd")), FVector(NewBeamLength - 50.0f, 0.0f, 0.0f));
}

void ABaseWaterGunBeamEffectActor::SetHitEffectActive(bool IsActive)
{
	if (HitEffectActorInstance == nullptr)
	{
		return;
	}
	
	HitEffectActorInstance->EffectSetActive(IsActive);
}

void ABaseWaterGunBeamEffectActor::UpdateBeamPosition_Implementation()
{
	FVector LocalStartPosition = BeamStartActor->GetActorLocation();
	FVector LocalEndPosition = BeamEndActor->GetActorLocation();
	
	if (BeamStartActor != nullptr)
	{
		LocalStartPosition = BeamStartActor->GetActorLocation() + (BeamDirectionNormal * GetWorld()->GetDeltaSeconds() * BeamStartMoveSpeed);
	}

	if (BeamEndActor != nullptr)
		LocalEndPosition = BeamEndActor->GetActorLocation() + BeamDirectionNormal * 100.f;

	Multicast_ApplyBeamPosition(LocalStartPosition, LocalEndPosition);
}

void ABaseWaterGunBeamEffectActor::Multicast_ApplyBeamPosition_Implementation(FVector LocalStartPosition, FVector LocalEndPosition)
{
	if (BeamStartActor)
		BeamStartActor->SetActorLocation(LocalStartPosition);

	SetActorLocation(LocalStartPosition);

	BeamLength = (BeamEndActor->GetActorLocation() - BeamStartActor->GetActorLocation()).Size();

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(BeamStartActor->GetActorLocation(), BeamEndActor->GetActorLocation()));

	NiagaraComp->SetVariableVec3(FName(TEXT("User.beamEnd")), FVector(BeamLength, 0.0f, 0.0f));
}
