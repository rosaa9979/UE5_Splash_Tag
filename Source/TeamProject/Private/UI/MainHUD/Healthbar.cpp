#include "UI/MainHUD/Healthbar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UHealthbar::NativeConstruct()
{
	Super::NativeConstruct();

	InitMaterial();
	InitBarState();	
	InitHP();
	InitAnimation();
}

void UHealthbar::UpdateCurHealth(float NewHealth)
{
	CurHealth = NewHealth;

	CurHealth = FMath::Clamp(CurHealth, 0, MaxHealth);

	if (Tb_HealthText)
	{
		Tb_HealthText->SetText(FText::AsNumber(CurHealth));
	}


	float UpdateHealthRate = CurHealth / MaxHealth;
	if (HealthBarDynMaterial)
	{
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("DefaultValue"), UpdateHealthRate);
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("Progress"), UpdateHealthRate);
	}
	UpdateTextPos();

	if (CurHealth >= 0)
	{
		IsDecreasing = true; 
		GetWorld()->GetTimerManager().SetTimer(IncreaseBarFillTimerHandle, this, &UHealthbar::IncreaseBar, 0.01f, true);

		if (CurHealth <= MaxHealth / 2)
			PlayAnimation(WarningBlinkAnimation);
		else
			PlayAnimation(BasicBlinkAnimation);
	}
}

void UHealthbar::InitMaterial()
{
	UMaterialInstanceDynamic* DynMaterial = Img_HealthBar->GetDynamicMaterial();
	if (DynMaterial)
	{
		HealthBarDynMaterial = DynMaterial;
	}
}

void UHealthbar::InitBarState()
{
	if (HealthBarDynMaterial)
	{
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("DefaultValue"), 1.0f);
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("Progress"), 1.0f);

		HealthBarDynMaterial->GetVectorParameterValue(TEXT("Active__Outer_RGBA"), DefaultActiveOuter);
		HealthBarDynMaterial->GetVectorParameterValue(TEXT("Active_RGBA"), DefaultActive);
		HealthBarDynMaterial->GetVectorParameterValue(TEXT("Default_RGBA"), Default);
		HealthBarDynMaterial->GetVectorParameterValue(TEXT("Inactive_Outer_RGBA"), DefaultInactiveOuter);
		HealthBarDynMaterial->GetVectorParameterValue(TEXT("Inactive_RGBA"), DefaultInactive);
	}

	if (Tb_HealthText)
	{
		Tb_HealthText->SetText(FText::FromString(TEXT("100")));
	}
}

void UHealthbar::InitHP()
{
	OldHealth = 100;
	CurHealth = 100;
	IsDecreasing = false;
}

void UHealthbar::InitAnimation()
{
	BasicBlinkEndDelegate.BindDynamic(this, &UHealthbar::OnBlinkAnimFinished);
	WarningBlinkEndDelegate.BindDynamic(this, &UHealthbar::OnBlinkAnimFinished);

	BindToAnimationFinished(BasicBlinkAnimation, BasicBlinkEndDelegate);
	BindToAnimationFinished(WarningBlinkAnimation, WarningBlinkEndDelegate);
}

void UHealthbar::IncreaseBar()
{
	//값 Update
	CurHealth += IncreaseHealthSpeed;
	OldHealth = CurHealth;

	//중단 조건
	if (CurHealth >= MaxHealth)
	{
		CurHealth = MaxHealth;
		OldHealth = MaxHealth;

		GetWorld()->GetTimerManager().ClearTimer(IncreaseBarFillTimerHandle);
	}

	//체력바 Update
	float UpdateHealthRate = CurHealth / MaxHealth;
	if (HealthBarDynMaterial)
	{
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("DefaultValue"), UpdateHealthRate);
		HealthBarDynMaterial->SetScalarParameterValue(TEXT("Progress"), UpdateHealthRate);
		UpdateTextPos();
		if (UpdateHealthRate > 0.5f)
		{
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Active__Outer_RGBA"), DefaultActiveOuter);
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Active_RGBA"), DefaultActive);
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Default_RGBA"), Default);
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Inactive_Outer_RGBA"), DefaultInactiveOuter);
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Inactive_RGBA"), DefaultInactive);
		}
		else
		{
			FLinearColor Red(1.0f, 0.0f, 0.0f, 0.6f);

			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Active__Outer_RGBA"), Red);

			Red.A = 0.8f;
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Active_RGBA"), Red);
			Red.A = 1.0f;
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Default_RGBA"), Red);
			Red.A = 0.2f;
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Inactive_Outer_RGBA"), Red);
			Red.A = 0.3f;
			HealthBarDynMaterial->SetVectorParameterValue(TEXT("Inactive_RGBA"), Red);
		}
	}
	//체력 Text Update
	if (Tb_HealthText)
		Tb_HealthText->SetText(FText::AsNumber((int)CurHealth));

}

void UHealthbar::UpdateTextPos()
{
	float CurHealthRate = CurHealth / MaxHealth;

	int CurPos = FMath::Lerp(MaxLeftTextPos, 0, CurHealthRate);
	CurPos = FMath::Clamp(CurPos, -275, 0);

	if (Tb_HealthText)
	{
		FWidgetTransform TextTransform;
		TextTransform.Translation = FVector2D(CurPos, 0);
		Tb_HealthText->SetRenderTransform(TextTransform);
	}
}

void UHealthbar::OnBlinkAnimFinished()
{
	if (CurHealth == MaxHealth)
		return;

	if (CurHealth <= MaxHealth / 2)
		PlayAnimation(WarningBlinkAnimation);
	else
		PlayAnimation(BasicBlinkAnimation);
}
