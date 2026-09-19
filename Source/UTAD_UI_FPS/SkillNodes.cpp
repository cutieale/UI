// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodes.h"
#include "SkillTree.h"
#include "Components/Button.h"	
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "UTAD_UI_FPSCharacter.h"
#include <Kismet/GameplayStatics.h>


void USkillNodes::NativeConstruct()
{
	Super::NativeConstruct();
	CH = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	BTN_SkillNode->OnPressed.AddDynamic(this, &USkillNodes::Press);
	BTN_SkillNode->OnReleased.AddDynamic(this, &USkillNodes::Release);
	BTN_SkillNode->OnHovered.AddDynamic(this, &USkillNodes::Hover);
	BTN_SkillNode->OnUnhovered.AddDynamic(this, &USkillNodes::Unhover);

	BTN_SkillNode->SetVisibility(ESlateVisibility::Visible);
	PB_SkillUpgrade->SetPercent(0);
	
		TXT_SkillName->SetText(FText::FromString(m_sSkillName));
		PB_SkillUpgrade->SetVisibility(ESlateVisibility::Visible);

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

	}	
}
void USkillNodes::Press()
{
	m_bPressed = true;
	m_fPressTime = 0.f;
	PB_SkillUpgrade->SetPercent(0.f);
	if(m_fPressTime >= m_fAcceptPressTime && CH->m_iSkillPoints >= m_iSkillCost)
	{
		if (bLocked)
		{
			if(m_aPreviousSkills.Num() > 0)
			{
				for (USkillNodes* PreviousSkill : m_aPreviousSkills)
				{
					if (PreviousSkill && !PreviousSkill->bLocked)
					{
						bPreviousSkillUnlocked = true;
						Unlock();
						NativeTick(FGeometry(), 0.f);
						TXT_SkillName->SetText(FText::FromString(m_sSkillName + " SKILL UNLOCKED"));
						break;
					}
				}
			}
			else
			{
				bPreviousSkillUnlocked = false;
				TXT_SkillName->SetText(FText::FromString(m_sSkillName + " NEEDS PREVIOUS SKILL UNLOCKED"));
			}
		}
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
	CH->m_iSkillPoints -= m_iSkillCost;
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

