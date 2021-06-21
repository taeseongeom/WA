// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WAGameModeBase.h"
#include "PlayerCharacter.h"
#include "Components/BillboardComponent.h"
#include "Door.h"
#include "WA.h"

AWAGameModeBase::AWAGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentRoomNum = 1;
}

void AWAGameModeBase::Init()
{
	UWorld* world = GetWorld();

	if (world)
	{
		for(const auto & entity : TActorRange<ARoomActor>(world))
		{
			rooms.Add(entity);
		}
		UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave0", 0));
		waInstance->SetCurrentStage(WASaveGameInstance->stageLevel);
		CurrentRoomNum = WASaveGameInstance->loadRoomNum;
		if (DebugRoomNum != 0)
			CurrentRoomNum = DebugRoomNum;

		for (int i = 0; i < rooms.Num(); i++)
		{
			for (int j = 0; j < rooms.Num(); j++)
			{
				if (i + 1 == rooms[j]->GetRoomNumber())
				{
					rooms.Swap(i, j);
					break;
				}
			}
			if (rooms[i]->GetRoomNumber() != CurrentRoomNum && !DebugMode)
			{
				DisableActor(rooms[i]);
			}
			rooms[i]->InitRoom();
		}
		for (TActorIterator<ADoor> iter(GetWorld()); iter; ++iter)
		{
			if (iter->GetName() ==
				FString("Gate" + FString::FromInt(CurrentRoomNum) +
					"_1"))
			{
				respawnPoint = iter->FindComponentByClass<UBillboardComponent>()
					->GetComponentLocation();
				break;
			}
		}
		maxRoomNumber = rooms.Num();
		for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Init SpawnPoint"), WASaveGameInstance->loadRoomNum);
			if (WASaveGameInstance->loadRoomNum == 1 || DebugRoomNum != 0)
				respawnPoint = iter->GetActorLocation();
			else if(!DebugMode)
				respawnPoint = WASaveGameInstance->saveRespawnPoint;
			iter->SetHealthPoint(WASaveGameInstance->health_point);
			iter->SetActorLocation(respawnPoint);
			break;
		}
	}
	state = EGameState::Play;
}

void AWAGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	state = EGameState::Load;
}

void AWAGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (state)
	{
	case EGameState::Load: Init(); break;
	case EGameState::Play: break;
	case EGameState::End: break;
	}
}

void AWAGameModeBase::AddInitPuzzle(ADefaultPuzzle* value, int roomNum){
	InitPuzzles.Add(roomNum, value);
}

void AWAGameModeBase::RoomReset(){
	for (TMultiMap<int8, ADefaultPuzzle*>::TKeyIterator iter = InitPuzzles.CreateKeyIterator(CurrentRoomNum);
		iter; ++iter)
		iter.Value()->InitializePuzzle();
}

void AWAGameModeBase::SetRespawnPoint(FVector point)
{
	respawnPoint = point;
}

void AWAGameModeBase::ChangeRoom(int8 roomNum, FVector resPoint)
{
	if ((roomNum > 0 || roomNum < maxRoomNumber
		|| CurrentRoomNum > 0) && !DebugMode)
	{
		EnableActor(rooms[roomNum - 1]);
		DisableActor(rooms[CurrentRoomNum - 1]);
	}
	CurrentRoomNum = roomNum;
	respawnPoint = resPoint;
}

void AWAGameModeBase::SetCurrentRoomNum(int8 value)
{
	CurrentRoomNum = value;
}

void AWAGameModeBase::DisableActor(AActor * target)
{
	TArray<AActor*> children;
	target->GetAttachedActors(children);

	if (children.Num() > 0)
	{
		for (int i = 0; i < children.Num(); i++)
		{
			DisableActor(children[i]);
		}
	}
	if (!target->IsHidden())
		target->SetActorHiddenInGame(true);
	if (target->GetActorEnableCollision())
		target->SetActorEnableCollision(false);
}

void AWAGameModeBase::EnableActor(AActor * target)
{
	TArray<AActor*> children;
	target->GetAttachedActors(children);

	if (children.Num() > 0)
	{
		for (int i = 0; i < children.Num(); i++)
		{
			EnableActor(children[i]);
		}
	}
	if (target->IsHidden())
		target->SetActorHiddenInGame(false);
	if (!target->GetActorEnableCollision())
		target->SetActorEnableCollision(true);
}

FVector AWAGameModeBase::GetRespawnPoint() const
{
	return respawnPoint;
}

void AWAGameModeBase::SetRoomSpawnPoint(int roomNum, FVector location)
{
	rooms[roomNum - 1]->SetRoomSpawnPoint(location);
}

