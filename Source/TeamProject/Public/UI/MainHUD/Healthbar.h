#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Healthbar.generated.h"

UCLASS()
class TEAMPROJECT_API UHealthbar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateCurHealth(float NewHP);

private:
	void InitMaterial();
	void InitBarState();
	void InitHP();
	void InitAnimation();

	void IncreaseBar();

	void UpdateTextPos();

	UFUNCTION()
	void OnBlinkAnimFinished();

private:
	//UI
	//--------------------------------
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Tb_HealthText;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_HealthBar;
	//--------------------------------

	//UI  Material
	//--------------------------------
	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* HealthBarDynMaterial;
	//--------------------------------

	//UI Animation
	//--------------------------------
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BasicBlinkAnimation;

	//스킬키가 눌리고 스킬 사용이 불가능한 경우 실행될 효과
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* WarningBlinkAnimation;

	FWidgetAnimationDynamicEvent BasicBlinkEndDelegate;
	FWidgetAnimationDynamicEvent WarningBlinkEndDelegate;
	//--------------------------------

	//체력 관련 변수
	//--------------------------------
	float OldHealth;
	float CurHealth;

	const float MaxHealth = 100;
	//--------------------------------

	//체력 업데이트 관련 변수
	//--------------------------------
	FTimerHandle IncreaseBarFillTimerHandle;		//체력 회복 이펙트 Timer
	float IncreaseHealthSpeed = 0.08f;				//체력 회복 속도

	bool IsDecreasing;
	
	//체력 Text 위치
	const int MaxLeftTextPos = -345;	
	//--------------------------------

	//체력 색 관련 변수
	//--------------------------------
	FLinearColor DefaultActiveOuter;
	FLinearColor DefaultActive;
	FLinearColor Default;
	FLinearColor DefaultInactiveOuter;
	FLinearColor DefaultInactive;
	//--------------------------------
	
};
