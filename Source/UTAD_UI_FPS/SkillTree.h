// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	UFUNCTION()
	void IsUnlocked(FString sId);
	UFUNCTION()
	void Acquire(FString sId);
};
