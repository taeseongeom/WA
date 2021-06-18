// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WA_API UWAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	int saveSlotIndex;
	int currentStage;
	int currentRoomNum;
public:
	void SetSaveSlotIndex(int value);
	int GetSaveSlotIndex() const;
	void SetCurrentStage(int value);
	int GetCurrentStage() const;
	void SetCurrentRoomNum(int value);
	int GetCurrentRoomNum() const;
};
