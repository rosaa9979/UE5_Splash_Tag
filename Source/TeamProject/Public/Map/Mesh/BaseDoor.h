// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDoor.generated.h"

class UBoxComponent;

UCLASS()
class TEAMPROJECT_API ABaseDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UFUNCTION()
	void HandleProgress(float Value);
	
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void SetBoxCollisionLocation(const FVector& Loc);
	UFUNCTION()
	void SetBoxCollisionRotation(const FRotator& Rot);
	UFUNCTION()
	void SetBoxCollisionScale(const FVector& Sca);

private:
	UPROPERTY(VisibleAnywhere)
	bool TB;
	UPROPERTY(VisibleAnywhere)
	float ReturnValueLeft;
	UPROPERTY(VisibleAnywhere)
	float ReturnValueRight;
};
