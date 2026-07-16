// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/TextBlock.h"

void UAmmoCounter::Show()
{
	AUTAD_UI_FPSCharacter* pCharacter = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());

	if (pCharacter)
	{
		pCharacter->OnTotalBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateTotalAmmo);
	
		UTP_WeaponComponent* pWeapon = pCharacter->GetAttachedWeaponComponent();
		if (pWeapon)
		{
			pWeapon->OnMagazineBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateCurrentAmmo);
		}
	}


	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAmmoCounter::Hide()
{
	AUTAD_UI_FPSCharacter* pCharacter = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());

	if (pCharacter)
	{
		pCharacter->OnTotalBulletsChanged.Unbind();

		UTP_WeaponComponent* pWeapon = pCharacter->GetAttachedWeaponComponent();
		if (pWeapon)
		{
			pWeapon->OnMagazineBulletsChanged.Unbind();
		}
	}


	SetVisibility(ESlateVisibility::Hidden);
}

void UAmmoCounter::UpdateCurrentAmmo(int NewCurrentAmmo)
{
	CurrentAmmo->SetText(FText::AsNumber(NewCurrentAmmo));
}

void UAmmoCounter::UpdateTotalAmmo(int NewTotalAmmo)
{
	//TotalAmmo->SetText(FText::AsNumber(NewTotalAmmo));
}
