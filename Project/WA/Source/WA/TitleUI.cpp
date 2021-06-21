// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUI.h"
#include "WA.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "PlayerCharacter.h"
#include "WASaveGame.h"
#include "WAGameInstance.h"
#include "WAViewportClient.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();
	slotIndex = 0;
	UWorld* world = GetWorld();
	if (world)
	{
		pc = world->GetFirstPlayerController();
	}
}

void UTitleUI::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!isPressed)
	{
		if (pc->WasInputKeyJustPressed(EKeys::AnyKey))
		{
			isPressed = true;
			isSelectingData = true;
			pressAnyKeyText->SetVisibility(ESlateVisibility::Collapsed);
			firstSaveDataBtn->SetVisibility(ESlateVisibility::Visible);
			secondSaveDataBtn->SetVisibility(ESlateVisibility::Visible);
			thirdSaveDataBtn->SetVisibility(ESlateVisibility::Visible);
			quitBtn->SetVisibility(ESlateVisibility::Visible);
			ChangeSlotImage(slotIndex);
		}
	}
	else
	{
		if (isSelectingData && !isGameStart)
		{
			if (pc->WasInputKeyJustPressed(EKeys::Left) && slotIndex > 0)
			{
				ChangeSlotImage(--slotIndex);
			}
			else if (pc->WasInputKeyJustPressed(EKeys::Right) && slotIndex < 2)
			{
				ChangeSlotImage(++slotIndex);
			}
			else if (pc->WasInputKeyJustPressed(EKeys::Down))
			{
				isSelectingData = false;
				quitBtn->SetBrushFromTexture(hoveredQuitTexture);
				ChangeSlotImage(-1);
			}
			else if (pc->WasInputKeyJustPressed(EKeys::Enter))
			{
				if (GetWorld()->GetGameInstance())
				{
					UWAViewportClient* waVP = Cast<UWAViewportClient>(GetWorld()->GetGameViewport());
					if (waVP)
					{
						waVP->Fade(1, true);
					}
					isGameStart = true;
				}
			}
		}
		else if(!isSelectingData && !isGameStart)
		{
			if (pc->WasInputKeyJustPressed(EKeys::Enter))
			{
				FGenericPlatformMisc::RequestExit(true);
			}
			else if (pc->WasInputKeyJustPressed(EKeys::Up))
			{
				isSelectingData = true;
				quitBtn->SetBrushFromTexture(normalQuitTexture);
				ChangeSlotImage(slotIndex);
			}
		}
		else if (isGameStart)
		{
			UWAViewportClient* waVP = Cast<UWAViewportClient>(GetWorld()->GetGameViewport());
			if (waVP->GetFadeAlpha() >= 1.0f)
			{
				waVP->ClearFade();
				StartGameFromSaveData();
			}
		}
	}
}

void UTitleUI::ChangeSlotImage(int _slotIndex)
{
	switch (_slotIndex)
	{
	case 0:
		firstSaveDataBtn->SetBrushFromTexture(hoveredSlotTexture);
		secondSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		thirdSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		break;
	case 1:
		firstSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		secondSaveDataBtn->SetBrushFromTexture(hoveredSlotTexture);
		thirdSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		break;
	case 2:
		firstSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		secondSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		thirdSaveDataBtn->SetBrushFromTexture(hoveredSlotTexture);
		break;
	default:
		firstSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		secondSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		thirdSaveDataBtn->SetBrushFromTexture(normalSlotTexture);
		break;
	}
}

void UTitleUI::StartGameFromSaveData()
{
	if (UWASaveGame* LoadedGame = Cast<UWASaveGame>(
		UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(slotIndex), 0)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Load"));
		UWAGameInstance* instance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		instance->SetCurrentStage(LoadedGame->stageLevel);
		instance->SetSaveSlotIndex(slotIndex);
		instance->SetCurrentRoomNum(LoadedGame->loadRoomNum);
		FString stageName = "Stage" + FString::FromInt(LoadedGame->stageLevel);
		UGameplayStatics::OpenLevel(GetWorld(), FName(*stageName));
	}
	else
	{
		if (UWASaveGame* SaveGame = Cast<UWASaveGame>(
			UGameplayStatics::CreateSaveGameObject(UWASaveGame::StaticClass())
			))
		{
			SaveGame->CreateFile(slotIndex);
			UGameplayStatics::OpenLevel(GetWorld(), FName("Stage1"));
			UE_LOG(LogTemp, Warning, TEXT("NEW"));
		}
	}
}
