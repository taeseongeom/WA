// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UInGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();


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
void UInGameUI::UpdateStamina(bool IsActive)
{

}

void UInGameUI::DisplayText(const FString& String)
{
	txt_dialog->SetText(FText::FromString(String));
}