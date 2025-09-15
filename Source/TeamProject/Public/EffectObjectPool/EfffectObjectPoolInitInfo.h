// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseEffectActor.h"
#include "EfffectObjectPoolInitInfo.generated.h"


USTRUCT()
struct FInitEffectActorInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseEffectActor> EffectActorClass;

	UPROPERTY(EditAnywhere)
	int InitSize = 5;
};

UCLASS()
class TEAMPROJECT_API UEfffectObjectPoolInitInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FInitEffectActorInfo> InitInfoArr;
	
};
