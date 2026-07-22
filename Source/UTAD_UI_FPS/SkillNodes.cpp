// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodes.h"
#include "SkillTree.h"



void USkillNodes::SetData(sSkillData* Data)
{
	BTN_SkillNode->OnPressed.AddDynamic(this, &USkillNodes::Press);
	BTN_SkillNode->OnReleased.AddDynamic(this, &USkillNodes::Release);
	BTN_SkillNode->OnHovered.AddDynamic(this, &USkillNodes::Hover);
	BTN_SkillNode->OnUnhovered.AddDynamic(this, &USkillNodes::Unhover);

	m_Data = Data;
	BTN_SkillNode->SetIsEnabled(!m_Data->bLocked);
	BTN_SkillNode->SetVisibility(ESlateVisibility::Visible);
	IMG_BGColorLocked->SetVisibility(m_Data->bLocked ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	IMG_BGColorUnlocked->SetVisibility(m_Data->bLocked ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	if (!m_Data->bLocked)
	{
		TXT_SkillName->SetText(FText::FromString(m_Data->sName));
	}
		PB_SkillUpgrade->SetPercent(0);
		m_fPressTime = 0.f;
}
void USkillNodes::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bPressed )
	{
		if (!m_Data->bLocked)
		{
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_Data->sName + " SKILL ALREADY UNLOCKED"));
			}
			m_bPressed = false;
			return;
		}
	
		if(m_Data->bLocked && !m_Data->pSkill)
		{
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_Data->sName + " SKILL LOCKED"));
			}
			m_bPressed = false;
			return;
		}
		if(!m_Data->bLocked && m_Data->pSkill)
		{
			m_Data->pSkill->IsUnlocked(m_Data->sParentId);
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_Data->sName + " NEEDS PREVIOUS SKILL UNLOCKED"));
			}
			m_bPressed = false;
		}
		{
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_Data->sName + " SKILL UNLOCKED"));
			}
			m_bPressed = false;
			return;
		}
	
		//m_fPressTime += InDeltaTime;
		
		//PB_SkillUpgrade->SetPercent(FMath::Min(2.f, m_fPressTime / m_fAcceptPressTime));
			
		
		/*	if (m_fPressTime >= m_fAcceptPressTime)
			{
				m_Data->pSkill->Acquire(m_Data->sId);
				m_Data->bLocked = false;
			}
			else if(m_Data->bLocked && m_Data->pSkill)
			{
				if (TXT_SkillName)
				{
					TXT_SkillName->SetText(FText::FromString(m_Data->sName + " SKILL TOO EXPENSIVE"));
				}
			}*/
		
		
	}
}
void USkillNodes::Press()
{
	m_bPressed = true;
	m_fPressTime = 0.f;
	PB_SkillUpgrade->SetPercent(0);
}
void USkillNodes::Release()
{
	m_bPressed = false;
	PB_SkillUpgrade->SetPercent(0);
	
}
void USkillNodes::Hover()
{
	if(m_Data->bLocked)
	{
		if (TXT_SkillName)
		{
			TXT_SkillName->SetText(FText::FromString(m_Data->sName + " $ " + FString::SanitizeFloat(m_Data->fRequirement)));
		}
	}
}
void USkillNodes::Unhover()
{
	if(TXT_SkillName)
	{
		TXT_SkillName->SetText(FText::FromString(m_Data->sName));
	}
}
