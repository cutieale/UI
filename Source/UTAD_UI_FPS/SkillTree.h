// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h" 
#include "Components/CanvasPanel.h" 
#include "SkillBubble.h"


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
	TObjectPtr<UImage> TreeRoot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> BubblesCanvasPanel;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<USkillBubble> SkillBubbleClass;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ButtonContinue;

	TMap<FString, USkillBubble::SSkillBubbleData> m_tSkillMap;



	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MoneyText;

	float m_fMoney = 210;

	UFUNCTION()
	void CreateTree();
	
	UFUNCTION()
	void Continue();

	UFUNCTION()
	void ShowTree();

	bool BuySkill(FString sId);

	bool IsUnlocked(FString sId);

	// https://forums.unrealengine.com/t/how-to-draw-lines-under-certain-widgets-ui-elements/2134979/2
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	

private:

	void CreateBubble(USkillBubble::SSkillBubbleData _oSkillBubbleData);


};
