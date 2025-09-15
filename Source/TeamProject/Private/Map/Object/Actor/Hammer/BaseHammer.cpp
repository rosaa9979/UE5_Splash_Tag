// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Object/Actor/Hammer/BaseHammer.h"

#include <memory>

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Components/BoxComponent.h"
#include "GameTag/STGamePlayTags.h"
#include "Net/Core/NetBitArray.h"
#include "Player/Character/Libraries/STFunctionLibrary.h"

ABaseHammer::ABaseHammer()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	HammerMeshHandle = CreateDefaultSubobject<UStaticMeshComponent>("HammerMeshHandle");
	HammerMeshHandle->SetupAttachment(Root);
	HammerMeshHead = CreateDefaultSubobject<UStaticMeshComponent>("HammerMeshHead");
	HammerMeshHead->SetupAttachment(HammerMeshHandle);
	HammerMeshTop = CreateDefaultSubobject<UStaticMeshComponent>("HammerMeshTop");
	HammerMeshTop->SetupAttachment(HammerMeshHandle);

	HammerMeshHandle->SetWorldScale3D(FVector(0.13f));
	// CollisionBox = CreateDefaultSubobject<UStaticMeshComponent>("CollisionBox");
	// CollisionBox->SetGenerateOverlapEvents(true);
	// CollisionBox->SetupAttachment(Root);
	// CollisionBox->SetHiddenInGame(true);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(RootComponent);
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ObjectTypeTag = STGamePlayTags::Object_Actor_Hammer;

	Interactable = true;
	bReplicates = true;
}

void ABaseHammer::BeginPlay()
{
	Super::BeginPlay();


	if (WeaponCollisionBox && HasAuthority())
	{
		// WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseHammer::ABaseHammer::OnOverlapBegin);
		// WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseHammer::ABaseHammer::OnOverlapEnd);
	}

	//SetCollision(true);
}

void ABaseHammer::SetCollision(bool bIsActive)
{
	if (bIsActive)
		WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	else
		WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseHammer::Server_PerformHammerSweep_Implementation()
{
	static const FName HammerSocketName = TEXT("HammerSocket");
	
	// Sweep 시작점: Hammer 중심
	const FVector Start = HammerMeshHead->GetSocketLocation(HammerSocketName);
	const FVector Forward = HammerMeshHead->GetSocketRotation(HammerSocketName).Vector();
	const FVector End = Start + Forward * 60.f;
	
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	const FVector Extent = FVector(40.f, 30.f, 25.f); // 박스 크기 (원하는 값으로 조절)
	const FQuat Rotation = FRotationMatrix::MakeFromX(Forward).ToQuat(); // 박스 회전

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		Rotation,
		ECC_Pawn,
		FCollisionShape::MakeBox(Extent),
		Params
	);
	
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && !OverlappedActors.Contains(HitActor))
			{
				OverlappedActors.Add(HitActor);

				// 정확한 FHitResult를 포함해 처리
				Multicast_ApplyCollision(HitActor, Hit);
			}
			/*
			if (OverlappedActors.Contains(HitActor))
			{
				OverlappedActors.Remove(HitActor);	
			}
			*/
		}
	}

	OverlappedActors.Empty();
}

// void ABaseHammer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
//                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	OnHammerHit(OtherActor, SweepResult);
// }
//
// void ABaseHammer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
// 	int32 OtherBodyIndex)
// {
// 	OnHammerHitEnd(OtherActor);
// }
//
//
// void ABaseHammer::OnHammerHit_Implementation(AActor* HitActor, const FHitResult& HitResult)
// {
// 	if (HitActor == nullptr)
// 		return;
// 	
// 	if (!OverlappedActors.Contains(HitActor))
// 	{
// 		OverlappedActors.Add(HitActor);
// 		
// 		Multicast_ApplyCollision(HitActor, HitResult);
// 	}
// }

// void ABaseHammer::OnHammerHitEnd_Implementation(AActor* HitActor)
// {
// 	if (OverlappedActors.Contains(HitActor))
// 	{
// 		OverlappedActors.Remove(HitActor);	
// 	}
// }

void ABaseHammer::Multicast_ApplyCollision_Implementation(AActor* HitActor, const FHitResult& HitResult)
{
	UAbilitySystemComponent* AbilitySystemComponent = USTFunctionLibrary::NativeGetParentAbilitySystemComponentFromActor(HitActor);
	if (AbilitySystemComponent != nullptr)
	{
		FGameplayEventData EventData;
		EventData.Instigator = this;
		EventData.Target = HitActor;
		EventData.EventTag = STGamePlayTags::Event_OnHammerHit;

		FGameplayAbilityTargetDataHandle TargetDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(HitResult);
    
		EventData.TargetData = TargetDataHandle;
		AbilitySystemComponent->HandleGameplayEvent(STGamePlayTags::Event_OnHammerHit, &EventData);
		//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitResult.GetActor(), STGamePlayTags::Event_OnHammerHit, EventData);

		if (!IsValid(HitActor) || !DamageGameplayEffectClass)
			return;
		
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageGameplayEffectClass, 1.f, EffectContext);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		
	}
	
}
