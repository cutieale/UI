// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h" 
#include "Components/TextBlock.h"



#include "SkillBubble.generated.h"
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillBubble : public UUserWidget
{
	GENERATED_BODY()

public:

	struct SSkillBubbleData
	{
		bool bLocked;

		float fPrice;

		FString sDescription;

		FString sId;
		FString sParentId;

		class USkillTree* pTree;

		USkillBubble* pWidget;

		FVector2D vPosition;
	};


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> AcceptProgressBar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Bubble;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillDescriptionText;

	

	SSkillBubbleData m_oSkillData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<UButton> m_pParent;

	void Initialize(SSkillBubbleData _oData);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void Press();

	UFUNCTION()
	void Release();

	UFUNCTION()
	void Hover();

	UFUNCTION()
	void UnHover();

	float m_fTimePressing;
	float m_fTimeToBuy = 1.f;

	bool m_bPressed = false;
	bool m_bHover = false;
};
