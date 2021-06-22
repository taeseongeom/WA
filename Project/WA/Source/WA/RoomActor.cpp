// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"
#include "CheckRoomClear.h"
#include "MovableBox.h"
#include "SwitchPuzzle.h"
#include "DefaultPuzzle.h"
#include "Door.h"
#include "WA.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARoomActor::InitPuzzleActors(AActor* actor)
{
	TArray<AActor*> children;
	actor->GetAttachedActors(children);
	if (children.Num() > 0)
	{
		for (int i = 0; i < children.Num(); i++)
		{
			InitPuzzleActors(children[i]);
		}
	}
	if (actor->IsA(ADefaultPuzzle::StaticClass()))
	{
		Cast<ADefaultPuzzle>(actor)->SetParentRoom(this);
	}
	if (actor->IsA(AMovableBox::StaticClass()))
	{
		boxActors.Add(actor);
	}
	if (actor->IsA(ASwitchPuzzle::StaticClass()))
	{
		switchActors.Add(actor);
	}
	for (int i = 0; i < checklist.Num(); i++)
	{
		Cast<ICheckRoomClear>(checklist[i])->SetClearCheckObject(true);
	}
}

int ARoomActor::GetRoomNumber() const
{
	return roomNumber;
}

bool ARoomActor::CheckClearList()
{
	for (int i = 0; i < checklist.Num(); i++)
	{
		if (!Cast<ICheckRoomClear>(checklist[i])->GetClear())
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Clear checklist RoomNum : %d"), roomNumber);
			return false;
		}
	}
	return true;
}

bool ARoomActor::InitRoom()
{
	UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
	InitPuzzleActors(this);
	if (waInstance)
	{
		LoadRoom();
		return true;
	}
	else
	{
		return false;
	}
}

void ARoomActor::SaveRoom()
{
	if (GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("Room Save : %d"), roomNumber);
		UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0));
		WASaveGameInstance->IsStageDatas(waInstance->GetCurrentStage());
		for (AActor* actor : boxActors)
		{
			WASaveGameInstance->stageDatas[waInstance->GetCurrentStage()].
				boxLocations.Add(actor->GetName(), actor->GetActorLocation());
		}
		for (AActor* actor : switchActors)
		{
			WASaveGameInstance->stageDatas[waInstance->GetCurrentStage()].
				isOnSwitchs.Add(
					actor->GetName(), Cast<ASwitchPuzzle>(actor)->IsInteracted());
		}
		WASaveGameInstance->stageDatas[waInstance->GetCurrentStage()].isRoomClears.Add(roomNumber, isClear);
		UGameplayStatics::SaveGameToSlot(WASaveGameInstance, "WASave" + FString::FromInt(0), WASaveGameInstance->playerIndex);
	}
}

void ARoomActor::LoadRoom()
{
	if (GetWorld())
	{
		UWorld* world = GetWorld();
		if (world->GetGameInstance())
		{
			UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
			if (UWASaveGame* LoadedGame = Cast<UWASaveGame>(
				UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0)))
			{
				if (LoadedGame->stageDatas.Contains(waInstance->GetCurrentStage()))
				{
					if (LoadedGame->stageDatas[waInstance->GetCurrentStage()].isRoomClears.Contains(roomNumber))
					{
						UE_LOG(LogTemp, Warning, TEXT("Save Data %d"), roomNumber);
					}
					if (LoadedGame->stageDatas[waInstance->GetCurrentStage()].isRoomClears.Contains(roomNumber))
						isClear = LoadedGame->stageDatas[waInstance->GetCurrentStage()].isRoomClears[roomNumber];
					else if (CheckClearList())
					{
						SaveRoom();
						UE_LOG(LogTemp, Warning, TEXT("This Room Auto Clear Room Num : %d"), roomNumber);
					}
					for (AActor* actor : boxActors)
					{
						if (LoadedGame->stageDatas[waInstance->GetCurrentStage()].
							boxLocations.Contains(actor->GetName()))
						{
							UE_LOG(LogTemp, Warning, TEXT("Save Box"), roomNumber);
							actor->SetActorLocation(LoadedGame->
								stageDatas[waInstance->GetCurrentStage()].
								boxLocations[actor->GetName()]);
						}
					}
					for (AActor* actor : switchActors)
					{
						if (LoadedGame->stageDatas[waInstance->GetCurrentStage()].
							isOnSwitchs.Contains(actor->GetName()))
						{
							if (LoadedGame->stageDatas[waInstance->GetCurrentStage()].
								isOnSwitchs[actor->GetName()])
							{
								UE_LOG(LogTemp, Warning, TEXT("Save Switch"), roomNumber);
								Cast<ASwitchPuzzle>(actor)->SetInteractedFlag(
									LoadedGame->stageDatas[waInstance->GetCurrentStage()].
									isOnSwitchs[actor->GetName()]);
								Cast<ASwitchPuzzle>(actor)->OnSwitchTarget();
							}
						}
					}
				}
			}
		}
	}
}

void ARoomActor::SetClear(bool value)
{
	isClear = value;
}

bool ARoomActor::GetClear() const
{
	return isClear;
}

FVector ARoomActor::GetRoomSpawnPoint() const
{
	return spawnPoint;
}

void ARoomActor::SetRoomSpawnPoint(FVector location)
{
	spawnPoint = location;
	UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), spawnPoint.X, spawnPoint.Y, spawnPoint.Z);
}
