// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RoomActor.h"
#include "WASaveGame.generated.h"

/**
 * 
 */
USTRUCT()
struct FStageRoomData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		TMap<FString, FVector> boxLocations;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		TMap<FString, bool> isOnSwitchs;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		TMap<int, bool> isRoomClears;
};

UCLASS()
class WA_API UWASaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UWASaveGame();
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int8 playerIndex;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector saveRespawnPoint;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int stageLevel;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int health_point;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int loadRoomNum;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	TMap<int, FStageRoomData> stageDatas;

public:
	void CreateFile(int saveSlotIndex);
	void Save(FVector respawnPoint, int health_point, int loadRoomNum, int saveSlotIndex, int currentStage);
	void Load(int saveSlotIndex);
	//void SaveRoomData(int saveSlotIndex, FRoomData data, int Stage, int RoomNum);
};
