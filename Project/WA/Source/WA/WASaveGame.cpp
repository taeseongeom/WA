// Fill out your copyright notice in the Description page of Project Settings.

#include "WA.h"

UWASaveGame::UWASaveGame()
{
	SlotName = TEXT("WASave");
	playerIndex = 0;
	for (int i = 0; i < 2; i++)
	{
		FStageRoomData srData;
		stageDatas.Add(i + 1, srData);
	}
}

void UWASaveGame::Save(FVector respawnPoint, int _health_point, int _loadRoomNum, int saveSlotIndex, int currentStage)
{
	SlotName = FString("WASave" + FString::FromInt(saveSlotIndex));
	saveRespawnPoint = respawnPoint;
	health_point = _health_point;
	loadRoomNum = _loadRoomNum;
	stageLevel = currentStage;
	UGameplayStatics::SaveGameToSlot(this, this->SlotName, this->playerIndex);
}

void UWASaveGame::Load(int saveSlotIndex)
{
}

//void UWASaveGame::SaveRoomData(int saveSlotIndex, FRoomData data, int Stage, int RoomNum)
//{
//	FRoomData rData;
//	rData.isClear = data.isClear;
//	rData.boxData = data.boxData;
//	rData.isSwitchOn = data.isSwitchOn;
//	if (!IsRoomCleared.Contains(Stage))
//	{
//		FStageData sData;
//		IsRoomCleared.Add(Stage, sData);
//		UE_LOG(LogTemp, Warning, TEXT("Add RoomSave"));
//	}
//	if (!IsRoomCleared[Stage].data.Contains(RoomNum))
//	{
//		FRoomData newRData;
//		IsRoomCleared[Stage].data.Add(RoomNum, newRData);
//	}
//	IsRoomCleared[Stage].data[RoomNum]= rData;
//	SlotName = FString("WASave" + FString::FromInt(saveSlotIndex));
//	UGameplayStatics::SaveGameToSlot(this, this->SlotName, this->playerIndex);
//}

void UWASaveGame::CreateFile(int saveSlotIndex)
{
	SlotName = FString("WASave" + FString::FromInt(saveSlotIndex));
	playerIndex = 0;
	health_point = 3;
	loadRoomNum = 1;
	stageLevel = 1;
	UGameplayStatics::SaveGameToSlot(this, this->SlotName, this->playerIndex);
}
