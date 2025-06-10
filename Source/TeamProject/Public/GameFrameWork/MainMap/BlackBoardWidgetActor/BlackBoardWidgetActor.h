#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackBoardWidgetActor.generated.h"

UCLASS()
class TEAMPROJECT_API ABlackBoardWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlackBoardWidgetActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* BlackBoardWidgetComponent;
};
