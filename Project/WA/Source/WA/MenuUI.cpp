// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"

#include "WAGameModeBase.h"
#include "WAAmbientSound.h"

#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"


void UMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	pc = GetWorld()->GetFirstPlayerController();
	index = 0;
	isVolumePanelOpen = false;
}

void UMenuUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 키 입력 받기
	if (pc->WasInputKeyJustPressed(EKeys::Down) || pc->WasInputKeyJustPressed(EKeys::Gamepad_DPad_Down))
	{
		if (isVolumePanelOpen)
		{
			float value = bar_gage->Percent - 0.2f;
			value = FMath::Max<float>(value, 0);
			bar_gage->SetPercent(value);
			SetVolume(value);
		}
		else
		{
			index++;
			index %= 3;
			if (index < 0)
				index += 3;
			Change(index);
		}
	}
	if (pc->WasInputKeyJustPressed(EKeys::Up) || pc->WasInputKeyJustPressed(EKeys::Gamepad_DPad_Up))
	{
		if (isVolumePanelOpen)
		{
			float value = bar_gage->Percent + 0.2f;
			value = FMath::Min<float>(value, 1);
			bar_gage->SetPercent(value);
			SetVolume(value);
		}
		else
		{
			index--;
			index %= 3;
			if (index < 0)
				index += 3;
			Change(index);
		}
	}
	if (pc->WasInputKeyJustPressed(EKeys::Enter) || pc->WasInputKeyJustPressed(EKeys::C) || pc->WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Bottom))
	{
		if (isVolumePanelOpen)
		{
			Select(1);
		}
		else
		{
			Select(index);
		}
	}
	/*if (pc->WasInputKeyJustPressed(EKeys::Escape) || pc->WasInputKeyJustPressed(EKeys::Gamepad_Special_Right))
	{
		Select(0);
	}*/
}

void UMenuUI::Change(int8 current_index)
{
	switch (current_index)
	{
	case 0:
		img_cancle->SetBrushFromTexture(hoveredSlotTexture);
		img_volume->SetBrushFromTexture(normalSlotTexture);
		img_title->SetBrushFromTexture(normalSlotTexture);
		break;

	case 1:
		img_cancle->SetBrushFromTexture(normalSlotTexture);
		img_volume->SetBrushFromTexture(hoveredSlotTexture);
		img_title->SetBrushFromTexture(normalSlotTexture);
		break;

	case 2:
		img_cancle->SetBrushFromTexture(normalSlotTexture);
		img_volume->SetBrushFromTexture(normalSlotTexture);
		img_title->SetBrushFromTexture(hoveredSlotTexture);
		break;
	}
}
void UMenuUI::Select(int8 current_index)
{
	switch (current_index)
	{
	case 0:
		RemoveFromViewport();
		GetWorld()->GetAuthGameMode<AWAGameModeBase>()->CloseMenu(0);
		break;

	case 1:
		// 볼륨 조절창 표시or제거
		if (isVolumePanelOpen)
		{
			pan_volume->SetVisibility(ESlateVisibility::Hidden);
			isVolumePanelOpen = false;
		}
		else
		{
			pan_volume->SetVisibility(ESlateVisibility::Visible);
			isVolumePanelOpen = true;
		}
		break;

	case 2:
		RemoveFromViewport();
		GetWorld()->GetAuthGameMode<AWAGameModeBase>()->CloseMenu(1);
		break;
	}
}
void UMenuUI::SetVolume(float volume)
{
	for (TActorIterator<AWAAmbientSound> iter(GetWorld()); iter; ++iter)
	{
		audio = *iter;
		break;
	}
	audio->SetBGMVolume(volume);
}