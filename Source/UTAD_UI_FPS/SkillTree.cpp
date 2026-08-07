// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SkillTree.h"

bool USkillTree::IsUnlocked(FString sId)
{
	if (sId == "starter")
	{
		return true;
	}
	USkillNodes::sSkillData* pData = m_SkillDataMap.Find(sId);
	if (pData)
	{
		return !pData->bLocked;
	}

	return false;
}

bool USkillTree::Acquire(FString sId)
{
	USkillNodes::sSkillData* pData = m_SkillDataMap.Find(sId);
	if(pData)
	{
		if (pData->bLocked && m_fPoints >= pData->fRequirement)
		{
			m_fPoints -= pData->fRequirement;
			pData->bLocked = false;
			return true;
			if(TXT_Points)
			{
				TXT_Points->SetText(FText::FromString(FString::SanitizeFloat(m_fPoints)));
			}
		}
	}
	return false;
}
void USkillTree::SetTree()
{
	BTN_CloseTree->OnClicked.AddDynamic(this, &USkillTree::HideTree);
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
void USkillTree::SetNode(USkillNodes::sSkillData m_Data)
{
	USkillNodes* pNode = CreateWidget<USkillNodes>(GetOwningPlayer(), SkillNodeClass);
	if(pNode && CanvasPanel_SkillTree)
	{
		UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(CanvasPanel_SkillTree->AddChild(pNode));
		if(pSlot)
		{
			pSlot->SetAutoSize(true);
			pSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			pSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			pSlot->SetPosition(m_Data.vPosition);
		}

		pNode->SetData(&m_Data);
		m_Data.pNodesWidget = pNode;
		m_SkillDataMap.Add(m_Data.sId, m_Data);
	}
}
