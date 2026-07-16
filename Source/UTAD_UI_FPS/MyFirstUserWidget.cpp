// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFirstUserWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

//UButton TryAgainButton
//UButton QuitButton
//UWidgetAnimation FadeIn


void UMyFirstUserWidget::NativeConstruct()
{
  TryAgainButton->OnClicked.AddDynamic(this, &UMyFirstUserWidget::TryAgain);
  QuitButton->OnClicked.AddDynamic(this, &UMyFirstUserWidget::Quit);
}

void UMyFirstUserWidget::Show()
{
  APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
  if (pPlayerController)
  {
    pPlayerController->SetInputMode(FInputModeUIOnly());
    //pPlayerController->Pause();
    pPlayerController->SetShowMouseCursor(true);
  
    PlayAnimation(FadeInAnimation);
  }

}

void UMyFirstUserWidget::TryAgain()
{
  APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
  if (pPlayerController)
  {
    pPlayerController->SetInputMode(FInputModeGameOnly());
    //pPlayerController->Pause();
    pPlayerController->SetShowMouseCursor(false);
    
    pPlayerController->RestartLevel();    
  }
}

void UMyFirstUserWidget::Quit()
{
  UKismetSystemLibrary::QuitGame(GetWorld(), NULL, EQuitPreference::Quit, true);
}
