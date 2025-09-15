// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatType/ChatType.h"
#include "Player/Character/BaseType/BaseStructType.h"
#include "PlayerMainHUD.generated.h"

class UAimDot;
class UPlayerItemSlot;
class UObjectInfoPanel;
class ABaseCharacter;
class USTAttributeSet;
struct FOnAttributeChangeData;
class UStaminaBar;
/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UPlayerMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetHandSlotText(FText Text);

	void SetHandSlot(const FItemData& InItemData);

	void ResetHandSlot();

	UFUNCTION()
	void UpdateWeaponStatusUI();

	// UFUNCTION(BlueprintCallable)
	// void SetBagSlotText(FText Text);
	//
	// UFUNCTION(BlueprintCallable)
	// void ChangeItemSlot();

	void UpdateRemainTime(int Second);

	void SetActiveMic(bool Active);

	UFUNCTION(BLueprintCallable)
	void PlayTalkingAnimation();

	void Init() const;
	void SetGameModeHUD(bool IsMissionMode);
	
	void AddAllChatSelfMessage(const FChatType & ChatType);
	void AddAllChatOtherMessage(const FChatType & ChatType, const FString& NickName);

	void AddTeamChatSelfMessage(const FChatType & ChatType);
	void AddTeamChatOtherMessage(const FChatType & ChatType, const FString& NickName);

	void SetPlayerJobText(const FString & JobText);
	void SetPlayerNickName(const FString & NickName);
	
	// 헬스바 접근 

	UFUNCTION(BlueprintCallable)
	UStaminaBar* GetStaminaBarWidget() const {return W_StaminaBar;}

	UFUNCTION(BlueprintCallable)
	UHealthBar* GetHealthBarWidget() const {return W_HealthBar;}

	UFUNCTION()
	UPlayerItemSlot* GetItemSlot() const { return W_PlayerHandSlot;}

	UFUNCTION()
	UAimDot* GetAimDot() const { return W_AimDot;}
	
	void ClearSmartPhone();

	void UpdateMissionAboveNumber(int RemainGraffitiCnt);
	void UpdateMissionTotalNumber(int TotalGraffitiCnt);
	
	// UI Attribute Delegate
	void InitializeHUD(APlayerController* PlayerController);

	void OnStaminaChanged(const FOnAttributeChangeData& Data);
	
	void OnHealthChanged(const FOnAttributeChangeData& Data);

	void HandleAbilitySystemInitialized(ABaseCharacter* Character);

	UObjectInfoPanel* GetObjectInfoPanel();

private:
	UPROPERTY()
	const USTAttributeSet* CachedAttributeSet;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UPlayerStateText> W_PlayerStateText;

	// UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	// TObjectPtr<class USpeedBar> W_SpeedBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UStaminaBar> W_StaminaBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UHealthBar> W_HealthBar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UPlayerItemSlot> W_PlayerHandSlot;

	// UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	// TObjectPtr<class UPlayerItemSlot> W_PlayerBagSlot;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_RemainMinute;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_PlayerID;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_PlayerJob;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> Tb_RemainSecond;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> Img_MicOn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UImage> Img_MicOff;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USmartPhone> W_SmartPhone;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UMissionWidget> W_MissionWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UObjectInfoPanel> W_ObjectInfoPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UAimDot> W_AimDot;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> TalkingAnimation;	
};
