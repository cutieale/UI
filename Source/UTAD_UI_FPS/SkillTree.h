// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h" 
#include "Components/CanvasPanel.h" 
#include "Components/TextBlock.h" 
#include "SkillNodes.h"
#include "SkillTree.generated.h"

/**
 * 
 */
class UCanvasPanel;
class UImage;
class UButton;
class UTextBlock;
class USkillNodes;

UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TSubclassOf<USkillNodes> SkillNodeClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI")
	TObjectPtr<UCanvasPanel> CanvasPanel_SkillTree;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI")
	TObjectPtr<UTextBlock> TXT_Points;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UI")
	TObjectPtr<UTextBlock> TXT_SkillTree;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_StarterMove;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_StarterHealth;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_StarterDmg;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Move2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Move3;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Health2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Health3;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Dmg2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	TObjectPtr<USkillNodes> SN_Dmg3;

	UFUNCTION()
	void HideTree();
	UFUNCTION()
	void ShowTree();

protected:
	virtual void NativeConstruct() override;



};
