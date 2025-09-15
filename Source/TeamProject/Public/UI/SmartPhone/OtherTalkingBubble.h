// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OtherTalkingBubble.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UOtherTalkingBubble : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInputText(const FText & InputText);
	void SetNickName(const FString & NickName);
	void SetImage(UMaterialInstanceDynamic * Material);
	void SetProfile(bool IsTaggerTalkingBubble);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> Img_TalkingBubble;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_InputText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class USizeBox> Sb_TalkingBubbleFrame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class USizeBox> Sb_Frame;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_NickName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> Img_TaggerProfile;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> Img_RunnerProfile;
	
	UPROPERTY(EditAnywhere)
	float WidthPaddingSize = 30;
};
