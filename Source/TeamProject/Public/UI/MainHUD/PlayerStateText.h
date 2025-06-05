#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateText.generated.h"

UCLASS()
class TEAMPROJECT_API UPlayerStateText : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerStateText(FText StateText);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Tb_PlayerStateText;
};
