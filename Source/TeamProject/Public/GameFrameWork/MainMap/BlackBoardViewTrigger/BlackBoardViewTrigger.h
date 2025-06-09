#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackBoardViewTrigger.generated.h"

UCLASS()
class TEAMPROJECT_API ABlackBoardViewTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlackBoardViewTrigger();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	class UBoxComponent * TriggerBox; 
	
};
