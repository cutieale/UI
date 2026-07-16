// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Crosshair.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "ReloadBar.h"

void UPlayerHUD::ShowNoWeapon()
{
  AmmoCounterWidget->Hide();
  CrosshairWidget->Hide();
  ReloadBarWidget->Hide();

  //PlayerHealthBarWidget->Show();
}

void UPlayerHUD::ShowAll()
{
  AmmoCounterWidget->Show();
  CrosshairWidget->Show();
  ReloadBarWidget->Show();

  //PlayerHealthBarWidget->Show();
}

void UPlayerHUD::Hide()
{
  AmmoCounterWidget->Hide();
  CrosshairWidget->Hide();
  ReloadBarWidget->Hide();

  //PlayerHealthBarWidget->Hide();
}
