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
	this->SetVisibility(ESlateVisibility::Hidden);
	if(TXT_Points)
	{
		TXT_Points->SetText(FText::FromString(FString::SanitizeFloat(m_fPoints)));
	}
	// Set up the skill tree nodes for movement speed upgrades
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = false;
		oSkill.fRequirement = 0.f;
		oSkill.sId = "Movement";
		oSkill.sParentId = "starter";
		oSkill.sName = "Movement Speed: 100 -> 150";
		oSkill.vPosition = FVector2D(-300.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = true;
		oSkill.fRequirement = 50.f;
		oSkill.sId = "Movement2";
		oSkill.sParentId = "Movement";
		oSkill.sName = "Movement Speed: 150 -> 200";
		oSkill.vPosition = FVector2D(-500.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = true;
		oSkill.fRequirement = 100.f;
		oSkill.sId = "Movement3";
		oSkill.sParentId = "Movement2";
		oSkill.sName = "Movement Speed: 200 -> 250";
		oSkill.vPosition = FVector2D(-700.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}

	// Set up the skill tree nodes for health upgrades
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = false;
		oSkill.fRequirement = 0.f;
		oSkill.sId = "Health";
		oSkill.sParentId = "starter";
		oSkill.sName = "Health: 100 -> 150";
		oSkill.vPosition = FVector2D(300.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = true;
		oSkill.fRequirement = 50.f;
		oSkill.sId = "Health2";
		oSkill.sParentId = "Health";
		oSkill.sName = "Health: 150 -> 200";
		oSkill.vPosition = FVector2D(500.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = true;
		oSkill.fRequirement = 100.f;
		oSkill.sId = "Health3";
		oSkill.sParentId = "Health2";
		oSkill.sName = "Health: 200 -> 250";
		oSkill.vPosition = FVector2D(700.f, 0.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}

	// Set up the skill tree nodes for damage upgrades
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = false;
		oSkill.fRequirement = 0.f;
		oSkill.sId = "Damage";
		oSkill.sParentId = "starter";
		oSkill.sName = "Damage: 100 -> 150";
		oSkill.vPosition = FVector2D(300.f, 350.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = false;
		oSkill.fRequirement = 50.f;
		oSkill.sId = "Damage2";
		oSkill.sParentId = "Damage";
		oSkill.sName = "Damage: 150 -> 200";
		oSkill.vPosition = FVector2D(500.f, 350.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}
	{
		USkillNodes::sSkillData oSkill;

		oSkill.bLocked = false;
		oSkill.fRequirement = 100.f;
		oSkill.sId = "Damage3";
		oSkill.sParentId = "Damage2";
		oSkill.sName = "Damage: 200 -> 250";
		oSkill.vPosition = FVector2D(700.f, 350.f);
		oSkill.pSkill = this;

		SetNode(oSkill);
	}

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
