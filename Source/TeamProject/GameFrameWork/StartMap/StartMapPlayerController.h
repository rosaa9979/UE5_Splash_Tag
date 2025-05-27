#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StartMapPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API AStartMapPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;	

private:
	void InitHUD();
	void InitInputMode();

private:
	UPROPERTY(EditAnywhere, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UStartMapHUD> StartMapHUDClass;

	UPROPERTY()
	class UStartMapHUD* StartMapHUD;

};
