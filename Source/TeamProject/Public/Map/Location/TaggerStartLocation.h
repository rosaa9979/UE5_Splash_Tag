#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaggerStartLocation.generated.h"

UCLASS()
class TEAMPROJECT_API ATaggerStartLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	ATaggerStartLocation();

protected:
	virtual void BeginPlay() override;
	
};
