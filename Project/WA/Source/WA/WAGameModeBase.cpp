// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WAGameModeBase.h"

AWAGameModeBase::AWAGameModeBase()
{
	CurrentRoomNum = 0;
}

void AWAGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWAGameModeBase::AddInitPuzzle(ADefaultPuzzle* value, int roomNum){
	InitPuzzles.Add(roomNum, value);
}

void AWAGameModeBase::RoomReset(){
	for (TMultiMap<int8, ADefaultPuzzle*>::TKeyIterator iter = InitPuzzles.CreateKeyIterator(CurrentRoomNum);
		iter; ++iter)
		iter.Value()->InitializePuzzle();
}