// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SkillNodes.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "UTAD_UI_FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SkillTree.h"


void USkillTree::HideTree()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
void USkillTree::ShowTree()
{
	this->SetVisibility(ESlateVisibility::Visible);
	FInputModeGameAndUI();
	
}
void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();
	TXT_Points->SetText(FText::FromString(FString::FromInt(CHInstance->m_iSkillPoints)));
}

