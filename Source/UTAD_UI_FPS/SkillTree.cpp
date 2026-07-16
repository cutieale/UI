// Fill out your copyright notice in the Description page of Project Settings.
#include "SkillTree.h"
// -------
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "Rendering/DrawElementTypes.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void USkillTree::CreateTree()
{

	this->SetVisibility(ESlateVisibility::Hidden);

	if (MoneyText)
	{
		MoneyText->SetText(FText::FromString(FString::SanitizeFloat(m_fMoney)));
	}
	
	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = false;
		oSkill.fPrice = -10;
		oSkill.sId = "MagazineSize1";
		oSkill.sParentId = "root";
		oSkill.pTree = this;
		oSkill.sDescription = "Magazine size : 10 -> 20";
		oSkill.vPosition = FVector2D(300, 50);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 20;
		oSkill.sId = "MagazineSize2";
		oSkill.sParentId = "MagazineSize1";
		oSkill.pTree = this;
		oSkill.sDescription = "Magazine size : 20 -> 30";
		oSkill.vPosition = FVector2D(500, 0);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 30;
		oSkill.sId = "AutomaticReload";
		oSkill.sParentId = "MagazineSize2";
		oSkill.pTree = this;
		oSkill.sDescription = "Gun reloads itself automaticaly";
		oSkill.vPosition = FVector2D(700, -100);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 30;
		oSkill.sId = "MagazineSize3";
		oSkill.sParentId = "MagazineSize2";
		oSkill.pTree = this;
		oSkill.sDescription = "Magazine size : 30 -> 40";
		oSkill.vPosition = FVector2D(700, 150);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 40;
		oSkill.sId = "MagazineSize4";
		oSkill.sParentId = "MagazineSize3";
		oSkill.pTree = this;
		oSkill.sDescription = "Magazine size : 40 -> 50";
		oSkill.vPosition = FVector2D(900, 100);

		CreateBubble(oSkill);
	}




	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = false;
		oSkill.fPrice = -10;
		oSkill.sId = "MoveSpeed1";
		oSkill.sParentId = "root";
		oSkill.pTree = this;
		oSkill.sDescription = "Movement speed : 5 -> 10";
		oSkill.vPosition = FVector2D(-250, 100);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 20;
		oSkill.sId = "MoveSpeed2";
		oSkill.sParentId = "MoveSpeed1";
		oSkill.pTree = this;
		oSkill.sDescription = "Movement speed : 10 -> 15";
		oSkill.vPosition = FVector2D(-450, 150);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 30;
		oSkill.sId = "MoveSpeed3";
		oSkill.sParentId = "MoveSpeed2";
		oSkill.pTree = this;
		oSkill.sDescription = "Movement speed : 15 -> 20";
		oSkill.vPosition = FVector2D(-650, 120);

		CreateBubble(oSkill);
	}



	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = false;
		oSkill.fPrice = -10;
		oSkill.sId = "FireRate1";
		oSkill.sParentId = "root";
		oSkill.pTree = this;
		oSkill.sDescription = "Fire rate : 5 -> 10";
		oSkill.vPosition = FVector2D(-300, -200);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 20;
		oSkill.sId = "FireRate2";
		oSkill.sParentId = "FireRate1";
		oSkill.pTree = this;
		oSkill.sDescription = "Fire rate : 10 -> 15";
		oSkill.vPosition = FVector2D(-500, -350);

		CreateBubble(oSkill);
	}

	{
		USkillBubble::SSkillBubbleData oSkill;
		oSkill.bLocked = true;
		oSkill.fPrice = 30;
		oSkill.sId = "FireRate3";
		oSkill.sParentId = "FireRate2";
		oSkill.pTree = this;
		oSkill.sDescription = "Fire rate : 15 -> 20";
		oSkill.vPosition = FVector2D(-700, -220);

		CreateBubble(oSkill);
	}

	ButtonContinue->OnClicked.AddDynamic(this, &USkillTree::Continue);
}


void USkillTree::Continue()
{
	//if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("USkillTree::Continue()"));

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
	if (this->GetVisibility() == ESlateVisibility::Visible)
	{
		this->SetVisibility(ESlateVisibility::Hidden);

		APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
		if (pPlayerController)
		{
			pPlayerController->SetInputMode(FInputModeGameOnly());
			pPlayerController->SetPause(false);
			pPlayerController->SetShowMouseCursor(false);
		}
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Visible);

		APlayerController* pPlayerController = GetOwningPlayer<APlayerController>();
		if (pPlayerController)
		{
			pPlayerController->SetInputMode(FInputModeUIOnly());
			pPlayerController->Pause();
			pPlayerController->SetShowMouseCursor(true);
		}
	}
}


bool USkillTree::BuySkill(FString sId)
{

	USkillBubble::SSkillBubbleData* pSkill = m_tSkillMap.Find(sId);
	if (pSkill)
	{
		if (pSkill->fPrice <= m_fMoney)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString("Skill bought: " + sId));
			m_fMoney -= pSkill->fPrice;
			pSkill->bLocked = false;

			if (MoneyText)
			{
				MoneyText->SetText(FText::FromString(FString::SanitizeFloat(m_fMoney)));
			}

			Invalidate(EInvalidateWidgetReason::Paint);

			return true;
		}
	}

	return false;
}

void USkillTree::CreateBubble(USkillBubble::SSkillBubbleData _oSkillBubbleData)
{


	USkillBubble* pBubble = CreateWidget<USkillBubble>(GetOwningPlayer(), SkillBubbleClass);
	if (pBubble && BubblesCanvasPanel)
	{
		UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(BubblesCanvasPanel->AddChild(pBubble));

		if (pCanvasSlot)
		{
			pCanvasSlot->SetAutoSize(true);
			pCanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			pCanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			pCanvasSlot->SetPosition(_oSkillBubbleData.vPosition); 
		}

		pBubble->Initialize(_oSkillBubbleData);

		_oSkillBubbleData.pWidget = pBubble;
		
		m_tSkillMap.Add(_oSkillBubbleData.sId, _oSkillBubbleData);
	}
}

bool USkillTree::IsUnlocked(FString sId)
{
	if (sId == "root")
	{
		return true;
	}

	USkillBubble::SSkillBubbleData* pSkill = m_tSkillMap.Find(sId);
	if (pSkill)
	{
		return !pSkill->bLocked;
	}

	return false;
}

int32 USkillTree::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 LayerID = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (BubblesCanvasPanel != nullptr)
	{
		for (const TPair<FString, USkillBubble::SSkillBubbleData>& rPair : m_tSkillMap)
		{
			const FString& sKey = rPair.Key;
			const USkillBubble::SSkillBubbleData& rData = rPair.Value;

			// Get the slot from the current node
			UCanvasPanelSlot* pCanvasSlot0 = Cast<UCanvasPanelSlot>(rData.pWidget->Slot);
			if (!pCanvasSlot0)
			{
				continue;
			}

			// Get the slot from the parent node, is no parent, use the tree root
			UCanvasPanelSlot* pCanvasSlot1 = UWidgetLayoutLibrary::SlotAsCanvasSlot(TreeRoot);

			const USkillBubble::SSkillBubbleData* pParentSkill = m_tSkillMap.Find(rData.sParentId);
			if (pParentSkill)
			{
				UCanvasPanelSlot* pCanvasSlotParent = Cast<UCanvasPanelSlot>(pParentSkill->pWidget->Slot);

				if (pCanvasSlotParent)
				{
					pCanvasSlot1 = pCanvasSlotParent;
				}
			}

			FVector2D AntchorPosition = BubblesCanvasPanel->GetCachedGeometry().GetLocalSize() * pCanvasSlot0->GetAnchors().Minimum;
			FVector2D Position0 = AntchorPosition + pCanvasSlot0->GetPosition();
			FVector2D Position1 = AntchorPosition + pCanvasSlot1->GetPosition();

			float fLineSize = (pParentSkill && pParentSkill->bLocked) ? 5.f : 10.f;

			FLinearColor oLineColor = (pParentSkill && pParentSkill->bLocked) ? FLinearColor::White : FLinearColor::Green;

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				50,
				BubblesCanvasPanel->GetPaintSpaceGeometry().ToPaintGeometry(),
				{ Position0,Position1 },
				ESlateDrawEffect::None,
				FLinearColor::Gray,
				true,
				10.f
			);

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				50,
				BubblesCanvasPanel->GetPaintSpaceGeometry().ToPaintGeometry(),
				{ Position0,Position1 },
				ESlateDrawEffect::None,
				oLineColor,
				true,
				5.f
			);
		}

		
	}
	return LayerID;
}

