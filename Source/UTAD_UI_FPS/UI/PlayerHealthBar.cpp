// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.25f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UPlayerHealthBar::Show()
{
	AUTAD_UI_FPSCharacter* pCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (pCharacter)
	{
		pCharacter->OnPlayerHealthChanged.BindUObject(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}

	SetVisibility(ESlateVisibility::HitTestInvisible);

}

void UPlayerHealthBar::Hide()
{
	AUTAD_UI_FPSCharacter* pCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (pCharacter)
	{
		pCharacter->OnPlayerHealthChanged.Unbind();
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	if (MaxHealth != 0)
	{
		PlayerHealthBar->SetPercent(static_cast<float>(NewHealth) / static_cast<float>(MaxHealth));
	}
}

void UPlayerHealthBar::LowHealthBlink()
{

}
