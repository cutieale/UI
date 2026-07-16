// Fill out your copyright notice in the Description page of Project Settings.
#include "SkillBubble.h"
#include "Components/CanvasPanelSlot.h"
#include "SkillTree.h"

void USkillBubble::Initialize(SSkillBubbleData _oData)
{
	Bubble->OnPressed.AddDynamic(this, &USkillBubble::Press);
	Bubble->OnReleased.AddDynamic(this, &USkillBubble::Release);

	Bubble->OnHovered.AddDynamic(this, &USkillBubble::Hover);
	Bubble->OnUnhovered.AddDynamic(this, &USkillBubble::UnHover);

	m_oSkillData = _oData;

	Bubble->SetBackgroundColor(FLinearColor::Gray);
	if (!m_oSkillData.bLocked)
	{
		Bubble->SetBackgroundColor(FLinearColor::White);
	}
	AcceptProgressBar->SetPercent(0);
}

void USkillBubble::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);





	if (m_bPressed)
	{
		if (!m_oSkillData.bLocked)
		{
			if (SkillDescriptionText)
			{
				SkillDescriptionText->SetText(FText::FromString("Already unlocked"));
			}
			m_bPressed = false;
			return;
		}

		if (!m_oSkillData.pTree)
		{
			return;
		}

		if (!m_oSkillData.pTree->IsUnlocked(m_oSkillData.sParentId))
		{
			if (SkillDescriptionText)
			{
				SkillDescriptionText->SetText(FText::FromString("Parent skill must be unlocked first"));
			}
			m_bPressed = false;
		}

		m_fTimePressing += InDeltaTime;

		AcceptProgressBar->SetPercent(FMath::Min(1.f, m_fTimePressing / m_fTimeToBuy));

		if (m_fTimePressing >= m_fTimeToBuy)
		{
			if(m_oSkillData.pTree->BuySkill(m_oSkillData.sId))
			{
				m_oSkillData.bLocked = false;
				Bubble->SetBackgroundColor(FLinearColor::White);
			}
			else if (SkillDescriptionText)
			{
				SkillDescriptionText->SetText(FText::FromString("Not enough money"));
			}
		}
	}
}

void USkillBubble::Press()
{
	m_bPressed = true;
	m_fTimePressing = 0.f;

	AcceptProgressBar->SetPercent(0.f);
}


void USkillBubble::Release()
{
	m_bPressed = false;

	AcceptProgressBar->SetPercent(0.f);

	if (SkillDescriptionText)
	{
		if (m_oSkillData.bLocked)
		{
			SkillDescriptionText->SetText(FText::FromString(m_oSkillData.sDescription + "\nPrice: " + FString::SanitizeFloat(m_oSkillData.fPrice)));
		}
		else
		{
			SkillDescriptionText->SetText(FText::FromString(m_oSkillData.sDescription));
		}
	}
}


void USkillBubble::Hover()
{
	m_bHover = true;

	if (SkillDescriptionText)
	{
		SkillDescriptionText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (m_oSkillData.bLocked)
		{
			SkillDescriptionText->SetText(FText::FromString(m_oSkillData.sDescription + "\nPrice: " + FString::SanitizeFloat(m_oSkillData.fPrice)));
		}
		else
		{
			SkillDescriptionText->SetText(FText::FromString(m_oSkillData.sDescription));
		}

		UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(Slot);
		if (pSlot)
		{
			pSlot->SetZOrder(999);
		}
	}
}

void USkillBubble::UnHover()
{
	m_bHover = false;
	if (SkillDescriptionText)
	{
		SkillDescriptionText->SetVisibility(ESlateVisibility::Hidden);

		UCanvasPanelSlot* pSlot = Cast<UCanvasPanelSlot>(Slot);
		if (pSlot)
		{
			pSlot->SetZOrder(500 );
		}
	}
}
