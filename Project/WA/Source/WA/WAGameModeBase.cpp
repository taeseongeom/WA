// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WAGameModeBase.h"
#include "PlayerCharacter.h"
#include "Components/BillboardComponent.h"
#include "Door.h"
#include "WAViewportClient.h"
#include "WAAmbientSound.h"
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
		UWAViewportClient* waVP = Cast<UWAViewportClient>(GetWorld()->GetGameViewport());
		if (waVP)
		{
			waVP->Fade(0, true);
		}
		for(const auto & entity : TActorRange<ARoomActor>(world))
		{
			rooms.Add(entity);
		}
		UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0));
		waInstance->SetCurrentStage(WASaveGameInstance->stageLevel);
		CurrentRoomNum = WASaveGameInstance->loadRoomNum;
		waInstance->SetCurrentRoomNum(CurrentRoomNum);
		if (DebugRoomNum != 0)
			CurrentRoomNum = DebugRoomNum;

		for (TActorIterator<AWAAmbientSound> iter(GetWorld()); iter; ++iter)
		{
			bgm = *iter;
			bgm->SetStage(waInstance->GetCurrentStage());
			bgm->SwapRoomBGM(waInstance->GetCurrentRoomNum());
			break;
		}
		
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
					"_1") && CurrentRoomNum != 1)
			{
				respawnPoint = iter->FindComponentByClass<UBillboardComponent>()
					->GetComponentLocation();
				break;
			}
		}
		maxRoomNumber = rooms.Num();
		if (!pc)
		{
			for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
			{
				pc = *iter;
				if (WASaveGameInstance->loadRoomNum == 1 || DebugRoomNum != 0)
					respawnPoint = iter->GetActorLocation();
				else if (!DebugMode)
					respawnPoint = WASaveGameInstance->saveRespawnPoint;
				pc->InitInGameUI();
				pc->SetHealthPoint(WASaveGameInstance->health_point);
				pc->SetActorLocation(respawnPoint);
				break;
			}
		}
		waVP->ClearFade();
	}
	state = EGameState::Play;
}

void AWAGameModeBase::ShowCutScene()
{
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
	}
	if (pc)
	{
		pc->InitInGameUI();
		pc->StartCutScene();
	}
}

void AWAGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
	if (UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave" + 
				FString::FromInt(waInstance->GetSaveSlotIndex()), 0)))
	{
		if (WASaveGameInstance->loadRoomNum == 1)
		{
			waInstance->SetCurrentStage(WASaveGameInstance->stageLevel);
			waInstance->SetCurrentRoomNum(1);
			waInstance->SetSaveSlotIndex(WASaveGameInstance->slotIndex);
			ShowCutScene();
			if (GetWorld())
			{
				for (TActorIterator<AWAAmbientSound> iter(GetWorld()); iter; ++iter)
				{
					bgm = *iter;
					bgm->SetStage(waInstance->GetCurrentStage());
					bgm->SwapRoomBGM(waInstance->GetCurrentRoomNum());
					break;
				}
			}
			if (pc)
			{
				UE_LOG(LogTemp, Warning, TEXT("NIGGA"));
				respawnPoint = pc->GetActorLocation();
				WASaveGameInstance->Save(respawnPoint,
					pc->GetHealthPoint(), 1,
					waInstance->GetSaveSlotIndex(), waInstance->GetCurrentStage());
			}
		}
		else
		{
			state = EGameState::Load;
		}
	}
	else
	{
		UWASaveGame* newSaveGameInstance =
			Cast<UWASaveGame>(UGameplayStatics::CreateSaveGameObject(UWASaveGame::StaticClass()));
		newSaveGameInstance->CreateFile(0);
		int i = 0;
		while (true)
		{
			if (UGameplayStatics::GetCurrentLevelName(GetWorld())
				== FString("Stage") + FString::FromInt(i))
				break;
			else
				i++;
		}
		waInstance->SetCurrentStage(i);
		waInstance->SetCurrentRoomNum(1);
		waInstance->SetSaveSlotIndex(0);
		newSaveGameInstance->Save(FVector::ZeroVector, 3, 1, 0, waInstance->GetCurrentStage());
		ShowCutScene();
		if (GetWorld())
		{
			for (TActorIterator<AWAAmbientSound> iter(GetWorld()); iter; ++iter)
			{
				bgm = *iter;
				bgm->SetStage(waInstance->GetCurrentStage());
				bgm->SwapRoomBGM(waInstance->GetCurrentRoomNum());
				break;
			}
		}
	}
}

void AWAGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (state)
	{
	case EGameState::CutScene:  break;
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
	bgm->SwapRoomBGM(CurrentRoomNum);
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

EGameState AWAGameModeBase::GetGameState() const
{
	return state;
}

void AWAGameModeBase::SetGameState(EGameState value)
{
	state = value;
}

void AWAGameModeBase::SetRoomSpawnPoint(int roomNum, FVector location)
{
	rooms[roomNum - 1]->SetRoomSpawnPoint(location);
}

