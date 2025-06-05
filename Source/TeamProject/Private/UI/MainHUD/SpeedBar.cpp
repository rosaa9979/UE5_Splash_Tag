#include "UI/MainHUD/SpeedBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USpeedBar::NativeConstruct()
{
	Super::NativeConstruct();

	InitMaterial();

	//test code
	//----------------
	CurSpeed = 500.0f;
	MaxSpeed = 600.0f;
	//----------------

	if (SpeedBarDynMaterial)
	{
		SpeedBarDynMaterial->SetScalarParameterValue(TEXT("DefaultValue"), -0.4);
	}
}

void USpeedBar::UpdateCurSpeed(float Speed)
{
	CurSpeed = Speed;
	CurSpeed = FMath::Clamp(CurSpeed, 0, MaxSpeed);
	float CurSpeedRate = CurSpeed / MaxSpeed;

	if (Tb_SpeedText)
		Tb_SpeedText->SetText(FText::AsNumber(CurSpeed / 100.0f));

	if (SpeedBarDynMaterial)
	{
		SpeedBarDynMaterial->SetScalarParameterValue(TEXT("Progress"), CurSpeedRate);
	}
}

void USpeedBar::InitMaterial()
{
	SpeedBarDynMaterial = Img_SpeedBar->GetDynamicMaterial();
}
