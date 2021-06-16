// Fill out your copyright notice in the Description page of Project Settings.


#include "WAGameInstance.h"

void UWAGameInstance::SetSaveSlotIndex(int value)
{
	saveSlotIndex = value;
}

int UWAGameInstance::GetSaveSlotIndex() const
{
	return saveSlotIndex;
}

void UWAGameInstance::SetCurrentStage(int value)
{
	currentStage = value;
}

int UWAGameInstance::GetCurrentStage() const
{
	return currentStage;
}

void UWAGameInstance::SetCurrentRoomNum(int value)
{
	currentRoomNum = value;
}

int UWAGameInstance::GetCurrentRoomNum() const
{
	return currentRoomNum;
}
