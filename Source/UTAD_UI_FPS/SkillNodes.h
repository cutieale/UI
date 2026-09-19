// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "SkillNodes.generated.h"

/**
 * 
 */
class UButton;
class USkillTree;

UENUM()
enum class ESkillType : uint8
{
	Health UMETA(DisplayName = "HEALTH"),
	Damage UMETA(DisplayName = "DAMAGE"),
	Movement UMETA(DisplayName = "MOVEMENT")
};
UCLASS()
class UTAD_UI_FPS_API USkillNodes : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI")
	TObjectPtr<UButton> BTN_SkillNode;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_SkillUpgrade;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_SkillName;

	UPROPERTY(EditAnywhere, Category = "TYPE")
	ESkillType m_eSkillType;

	UPROPERTY(EditAnywhere, Category = "ID")
	FString m_sSkillId;

	UPROPERTY(EditAnywhere, Category = "NAME")
	FString m_sSkillName;

	UPROPERTY(EditAnywhere, Category = "PREV")
	TArray<USkillNodes*> m_aPreviousSkills;
	UPROPERTY(EditAnywhere, Category = "COST")
	int32 m_iSkillCost;
	
	bool bLocked = true;
	bool bPreviousSkillUnlocked = false;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	class AUTAD_UI_FPSCharacter* CH;

	UFUNCTION()
	void Press();
	UFUNCTION()
	void Release();
	UFUNCTION()
	void Hover();
	UFUNCTION()
	void Unhover();
	UFUNCTION()
	 void Unlock();

	float m_fAcceptPressTime = 2.f;
	float m_fPressTime;

	bool m_bPressed;
	bool m_bHovered;

	virtual void NativeConstruct() override;
};
