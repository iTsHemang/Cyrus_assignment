// Fill out your copyright notice in the Description page of Project Settings.


#include "UI.h"
#include "TimerManager.h"
#include "BoxSpawner.h"
#include "Components/TextBlock.h"

void UUI::setscore(FString bName, int32 bScore)
{
    //Display tottal score
	score += bScore;
    FString ScoreString = FString::Printf(TEXT("Score: %d"), score);
	scoreText->SetText(FText::FromString(ScoreString));
	
	//Display box name and set text box visibility to visible
	nameText->SetVisibility(ESlateVisibility::Visible);
	nameText->SetText(FText::FromString(bName));
    
    //Delay to hide name text box
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &UUI::HideName, 2.0f, false);
}

void UUI::HideName()
{
    //Setting name text box visibility to collapsed
	nameText->SetVisibility(ESlateVisibility::Collapsed);
}

