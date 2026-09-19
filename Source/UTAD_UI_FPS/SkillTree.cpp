// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SkillNodes.h"
#include "SkillTree.h"


void USkillTree::HideTree()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
void USkillTree::ShowTree()
{
	this->SetVisibility(ESlateVisibility::Visible);
}
void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();
}

