// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h" 
#include "Components/CanvasPanel.h" 
#include "SkillNodes.h"
#include "SkillTree.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TSubclassOf<USkillNodes> SkillNodeClass;

	TMap<FString, USkillNodes::sSkillData> m_SkillDataMap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_SkillTree;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> IMG_Tree;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BTN_CloseTree;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_Points;
	float m_fPoints = 0.f;

	bool IsUnlocked(FString sId);
	bool Acquire(FString sId);

	UFUNCTION()
	void SetTree();
	UFUNCTION()
	void HideTree();
	UFUNCTION()
	void ShowTree();

private:
	void SetNode(USkillNodes::sSkillData m_Data);


};
