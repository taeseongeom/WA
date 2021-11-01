// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UInGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DisplayText("");

	cutSceneNum = 0;
	waitTime = 0.0f;
	timer = 0.0f;
}

void UInGameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (waitTime > 0)
	{
		if (timer < waitTime)
		{
			timer += InDeltaTime;
		}
		else
		{
			waitTime = 0.0f;
			timer = 0.0f;
			DisplayText("");
		}
	}
}

void UInGameUI::UpdateHealthBar(int HealthPoint)
{
	switch (HealthPoint)
	{
	case 0:
		img_health_0->SetOpacity(false);
		img_health_1->SetOpacity(false);
		img_health_2->SetOpacity(false);
		break;

	case 1:
		img_health_0->SetOpacity(true);
		img_health_1->SetOpacity(false);
		img_health_2->SetOpacity(false);
		break;

	case 2:
		img_health_0->SetOpacity(true);
		img_health_1->SetOpacity(true);
		img_health_2->SetOpacity(false);
		break;

	case 3:
		img_health_0->SetOpacity(true);
		img_health_1->SetOpacity(true);
		img_health_2->SetOpacity(true);
		break;
	}
}

void UInGameUI::DisplayText(const FString& String, float Duration)
{
	if (String.IsEmpty())
		img_dialog->SetOpacity((false));
	else
		img_dialog->SetOpacity((true));

	txt_dialog->SetText(FText::FromString(String));
	waitTime = Duration;
}

bool UInGameUI::NextCutScene(int stage)
{
	cutSceneNum++;
	FString key = FString::FromInt(stage) + "_" + FString::FromInt(cutSceneNum);
	if (cutScenes.Contains(key))
	{
		img_cutscene->SetBrushFromTexture(cutScenes[key]);
		return false;
	}
	return true;
}
void UInGameUI::EnableCutScene(int stage)
{
	FString key = FString::FromInt(stage) + "_" + FString::FromInt(cutSceneNum);
	if (cutScenes.Contains(key))
	{
		img_cutscene->SetBrushFromTexture(cutScenes[key]);
	}
	img_cutscene->SetOpacity(true);
}
void UInGameUI::DisableCutScene()
{
	img_cutscene->SetOpacity(false);
}
