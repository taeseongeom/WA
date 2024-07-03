// Fill out your copyright notice in the Description page of Project Settings.


#include "WAAmbientSound.h"
#include "Components/AudioComponent.h"
#include "WA.h"

void AWAAmbientSound::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		UWAGameInstance* waInstance =
			Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		if (waInstance)
		{
			stage = waInstance->GetCurrentStage();
		}
		else
		{
			stage = 0;
		}
	}
	currentPlayIndex = 0;
}

void AWAAmbientSound::SwapRoomBGM(int roomNum)
{
	UE_LOG(LogTemp, Warning, TEXT("%d, %d"), stage, roomNum);
	if (stage == 2)
	{
		switch (currentPlayIndex)
		{
		case 0:
			if (roomNum >= 10 && roomNum <= 16)
			{
				currentPlayIndex = 1;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 1 || roomNum == 2 || roomNum == 17)
			{
				currentPlayIndex = 2;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 18)
			{
				currentPlayIndex = 3;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			break;
		case 1:
			if (roomNum >= 3 && roomNum <= 9)
			{
				currentPlayIndex = 0;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 1 || roomNum == 2 || roomNum == 17)
			{
				currentPlayIndex = 2;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 18)
			{
				currentPlayIndex = 3;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			break;
		case 2:
			if (roomNum >= 3 && roomNum <= 9)
			{
				currentPlayIndex = 0;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum >= 10 && roomNum <= 16)
			{
				currentPlayIndex = 1;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 18)
			{
				currentPlayIndex = 3;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			break;
		case 3:
			if (roomNum >= 3 && roomNum <= 9)
			{
				currentPlayIndex = 0;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum >= 10 && roomNum <= 16)
			{
				currentPlayIndex = 1;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
			else if (roomNum == 1 || roomNum == 2 || roomNum == 17)
			{
				currentPlayIndex = 2;
				GetAudioComponent()->SetSound(bgms[currentPlayIndex]);
				GetAudioComponent()->Play();
			}
		}
	}
}
void AWAAmbientSound::MuteBGM()
{
	GetAudioComponent()->Stop();
}
void AWAAmbientSound::SetBGMVolume(float value)
{
	GetAudioComponent()->SetVolumeMultiplier(value);
}

void AWAAmbientSound::SetStage(int value)
{
	stage = value;
}
