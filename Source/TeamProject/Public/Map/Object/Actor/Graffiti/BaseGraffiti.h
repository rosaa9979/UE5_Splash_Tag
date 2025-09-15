// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/Object/Actor/BaseObject.h"
#include "Net/UnrealNetwork.h"
#include "BaseGraffiti.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ABaseGraffiti : public ABaseObject
{
	GENERATED_BODY()

	ABaseGraffiti();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GraffitiMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* BaseMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMaterialInstanceDynamic* DynamicMaterial;

public:
	virtual void BeginPlay() override;

	bool GetIsErased() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float EraseRatio = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MinRatio = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxRatio = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EraseSpeed = 0.01f;
	
	UPROPERTY(Replicated)
	bool bIsErased = false;

public:
	UFUNCTION(BlueprintCallable)
	void OnHitBySplash(AActor* HitActor);

	UFUNCTION(Server, Reliable)
	void Server_Request_OnSplashHit(AActor* HitActor);

	UFUNCTION(NetMulticast, Reliable)
	void Apply_OnSplashHit(float NewEraseRatio);

	virtual FText GetObjectName() override;
	virtual FText GetDescription() override;

private:
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
