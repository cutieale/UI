// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyFirstUserWidget.generated.h"


class UButton;
class UWidgetAnimation;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UMyFirstUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> TryAgainButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;


	UPROPERTY(Transient, meta = (BindWidgetAnimation))
	TObjectPtr<UWidgetAnimation> FadeInAnimation;
	

	void Show();

private:

	UFUNCTION()
	void TryAgain();

	UFUNCTION()
	void Quit();

protected:
	virtual void NativeConstruct() override;
};
