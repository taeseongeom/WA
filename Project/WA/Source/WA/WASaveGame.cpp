// Fill out your copyright notice in the Description page of Project Settings.


#include "WASaveGame.h"
#include "WA.h"
#include "Kismet/GameplayStatics.h"

UWASaveGame::UWASaveGame()
{

}

void UWASaveGame::Save(int slotIndex, int _stageLevel, int _health_point, int _loadRoomNum)
{
	SaveSlotName = "WA_" + FString::FromInt(slotIndex);
	SaveIndex = 0;
	stageLevel = _stageLevel;
	health_point = _health_point;
	loadRoomNum = _loadRoomNum;
	UGameplayStatics::SaveGameToSlot(this, this->SaveSlotName, this->SaveIndex);
}

void UWASaveGame::Load(int slotIndex)
{
}
