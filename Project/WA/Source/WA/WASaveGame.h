// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WASaveGame.generated.h"

/**
 * 
 */
UCLASS()
class WA_API UWASaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UWASaveGame();

	UPROPERTY()
	FString SaveSlotName;
	
	UPROPERTY()
	int32 SaveIndex;

	UPROPERTY()
	int stageLevel;

	UPROPERTY()
	int health_point;

	UPROPERTY()
	int loadRoomNum;

public:
	void Save(int slotIndex, int stageLevel, int health_point, int loadRoomNum);
	void Load(int slotIndex);
};
