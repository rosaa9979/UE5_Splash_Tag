// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/SmartPhone/SmartPhoneEnumType.h"
#include "ChatType/ChatType.h"
#include "ChattingRoom.generated.h"

UCLASS()
class TEAMPROJECT_API UChattingRoom : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(class USmartPhone * Target);
	void Clear();

	void AddChatSelfMessage(const FChatType & ChatType);
	void AddChatOtherMessage(const FChatType & ChatType, const FString & NickName);

	void FocusOn();
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void GoToChattingRoomList();

	UFUNCTION()
	void FocusInputEditTextBox();

	UFUNCTION()
	void TextCommit(const FText& Text, ETextCommit::Type Type);	
	
	UFUNCTION()
	void ClickedEmoListOpenButton();
	
private:
	void AddTalkingBubble(UWidget * AddWidget);
	void InitRoomType();
	void InitEmojiList();

	UMaterialInstanceDynamic * TargetMaterial(EEmojiType EmojiType);
	
protected:
	UPROPERTY()
	TObjectPtr<class USmartPhone> SmartPhone;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UButton> Btn_TabletBack;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UTextBlock> Tb_RoomName;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UBorder> B_InputTextBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UEditableText> Etb_InputText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UVerticalBox> Vb_TalkingBubble;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UScrollBox> Scb_MsgScroll;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class USizeBox> Sb_EmoList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UButton> Btn_EmoListOpenButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UWrapBox> WB_EmojiList;
	
	UPROPERTY(EditAnywhere)
	EChattingRoomType RoomType;
	
	UPROPERTY(EditAnywhere, Category = "TalkingBubble", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class USelfTalkingBubble>  SelfTalkingBubbleClass;

	UPROPERTY(EditAnywhere, Category = "TalkingBubble", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UOtherTalkingBubble>  OtherTalkingBubbleClass;
	
};
