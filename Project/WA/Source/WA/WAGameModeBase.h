// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultPuzzle.h"
#include "WAGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WA_API AWAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void AddInitPuzzle(ADefaultPuzzle* value, int roomNum);
	void RoomReset();
	AWAGameModeBase();
	virtual void BeginPlay() override;
private:
	//UPROPERTY 사용 불가능한데 추후 수정필요
	TMultiMap<int8, ADefaultPuzzle*> InitPuzzles;
public:
	UPROPERTY(EditAnywhere)
	int8 MaxRoomCount;

	UPROPERTY()
	int8 CurrentRoomNum;
};
