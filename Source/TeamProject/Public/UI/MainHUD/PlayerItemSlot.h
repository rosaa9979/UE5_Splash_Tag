#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UPlayerItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void SetSlotTypeText(FText SlotTypeText);
	void SetItemName(FText Name);

	FText GetItemName() const { return ItemName; }
private:
	void ChangeSize();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Tb_SlotTypeText;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* Sb_Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Tb_ItemName;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* Sb_Frame;

	FText ItemName;

	//사이즈 변경 관련 변수
	//--------------------------------------
	const float SizeChangeSpeed = 5.f;

	FTimerHandle SizeChangeTimerHandle;

	double TargetWidthSize;
	double CurWidthSize;

	bool IsIncreaseSize;
	//--------------------------------------
};
