// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SkillNodes.h"
#include "SkillTree.h"

bool USkillTree::IsUnlocked(FString sId)
{
	if (sId == "starter")
	{
		return true;
	}

	return false;
}


void USkillTree::HideTree()
{
	APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
	if (pPlayerController)
	{
		pPlayerController->SetInputMode(FInputModeGameOnly());
		pPlayerController->SetPause(false);
		pPlayerController->SetShowMouseCursor(false);
	}

	this->SetVisibility(ESlateVisibility::Hidden);
}
void USkillTree::ShowTree()
{
	APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
	if (pPlayerController)
	{
		pPlayerController->SetInputMode(FInputModeUIOnly());
		pPlayerController->Pause();
		pPlayerController->SetShowMouseCursor(true);
	}

	this->SetVisibility(ESlateVisibility::Visible);
}
void USkillTree::NativeConstruct()
{
}

