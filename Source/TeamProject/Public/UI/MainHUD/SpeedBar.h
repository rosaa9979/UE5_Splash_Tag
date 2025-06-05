#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeedBar.generated.h"

UCLASS()
class TEAMPROJECT_API USpeedBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void UpdateCurSpeed(float Speed);

private:
	void InitMaterial();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Tb_SpeedText;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_SpeedBar;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* SpeedBarDynMaterial;

	float MaxSpeed;
	float CurSpeed;
};
