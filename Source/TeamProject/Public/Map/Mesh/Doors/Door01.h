// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/Mesh/BaseDoor.h"
#include "Door01.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ADoor01 : public ABaseDoor
{
	GENERATED_BODY()

	ADoor01();

protected:
	void BeginPlay() override;
	
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* LeftDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* RightDoorMesh;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
