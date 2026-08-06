// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "SkillNodes.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillNodes : public UUserWidget
{
	GENERATED_BODY()
public:

	struct sSkillData
	{
		bool bLocked;
		float fRequirement;

		FString sName;

		FString sId;
		FString sParentId;
		
		class USkillTree* pSkill;
		USkillNodes* pNodesWidget;
	};
	sSkillData* m_Data;
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BTN_SkillNode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_SkillUpgrade;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_SkillName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IMG_BGColorLocked;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IMG_BGColorUnlocked;


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetData(sSkillData* Data);

protected:
	UFUNCTION()
	void Press();
	UFUNCTION()
	void Release();
	UFUNCTION()
	void Hover();
	UFUNCTION()
	void Unhover();

public:
	float m_fAcceptPressTime = 2.f;
	float m_fPressTime = 0.f;

	bool m_bPressed;
	bool m_bHovered;
};
