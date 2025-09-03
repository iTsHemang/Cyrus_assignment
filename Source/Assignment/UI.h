// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "UI.generated.h"


class UCanvasPanel;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ASSIGNMENT_API UUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* scoreText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UTextBlock* nameText;
	
	UPROPERTY()
	int32 score = 0;

	UFUNCTION()
	void setscore(FString bName, int32 bScore);

	UFUNCTION()
	void HideName();
};
