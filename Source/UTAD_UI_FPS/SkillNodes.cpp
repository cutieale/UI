// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodes.h"
#include "SkillTree.h"
#include "Components/Button.h"	


void USkillNodes::NativeConstruct()
{
	Super::NativeConstruct();

	BTN_SkillNode->OnPressed.AddDynamic(this, &USkillNodes::Press);
	BTN_SkillNode->OnReleased.AddDynamic(this, &USkillNodes::Release);
	BTN_SkillNode->OnHovered.AddDynamic(this, &USkillNodes::Hover);
	BTN_SkillNode->OnUnhovered.AddDynamic(this, &USkillNodes::Unhover);

	BTN_SkillNode->SetVisibility(ESlateVisibility::Visible);
	PB_SkillUpgrade->SetPercent(0);
	
	if (!bLocked)
	{
		TXT_SkillName->SetText(FText::FromString(m_sSkillName));
		PB_SkillUpgrade->SetVisibility(ESlateVisibility::Hidden);
	}
}
void USkillNodes::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_bPressed)
	{
		if (!bLocked)
		{
			switch (m_eSkillType)
			{
				case ESkillType::Health:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL ALREADY UNLOCKED"));
					}
					m_bPressed = false;
					return;
					break;
				case ESkillType::Damage:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL ALREADY UNLOCKED"));
					}
					m_bPressed = false;
					return;
					break;
				case ESkillType::Movement:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL ALREADY UNLOCKED"));
					}
					m_bPressed = false;
					return;
					break;
			}
			bLocked = false;
		}

		if (bLocked)
		{
			switch (m_eSkillType)
			{
				case ESkillType::Health:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL LOCKED"));
					}
					break;
				case ESkillType::Damage:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL LOCKED"));
					}
					break;
				case ESkillType::Movement:
					if (TXT_SkillName)
					{
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL LOCKED"));
					}
					break;
				
			}
			m_bPressed = false;
			return;
		}
		if (!bLocked)
		{
			
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_sSkillName + " NEEDS PREVIOUS SKILL UNLOCKED"));
			}
			m_bPressed = false;
		}
		{
			if (TXT_SkillName)
			{
				TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL UNLOCKED"));
			}
			m_bPressed = false;
			return;
		}
	
	}	
}
void USkillNodes::Press()
{
	m_bPressed = true;
	m_fPressTime = 0.f;
	PB_SkillUpgrade->SetPercent(0.f);
	if(m_fPressTime >= m_fAcceptPressTime)
	{
		Unlock();
		PB_SkillUpgrade->SetPercent(1.f);
	}
}
void USkillNodes::Release()
{
	m_bPressed = false;
	PB_SkillUpgrade->SetPercent(0.f);
	
}
void USkillNodes::Hover()
{
	if(bLocked)
	{
		if (TXT_SkillName)
		{
			TXT_SkillName->SetText(FText::FromString(m_sSkillName + " $ " + FString::SanitizeFloat(m_iSkillCost)));
		}
	}
	else if (!bLocked)
	{
		if (TXT_SkillName)
		{
			TXT_SkillName->SetText(FText::FromString(m_sSkillName));
		}
	}
}
void USkillNodes::Unhover()
{
	if(TXT_SkillName)
	{
		TXT_SkillName->SetText(FText::FromString(m_sSkillName));
	}
}

void USkillNodes::Unlock()
{
	FButtonStyle NewButtonStyle = BTN_SkillNode->GetStyle();
	if (!bLocked)
	{
		NewButtonStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	}
	if (bLocked)
	{
		NewButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor::Red);
	}
}

