// Fill out your copyright notice in the Description page of Project Settings.
#include "SwitchPuzzle.h"
#include "Switchable.h"
#include "WA.h"
#include "RoomActor.h"
#include "PlayerCharacter.h"

// Sets default values
ASwitchPuzzle::ASwitchPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	timerFlag = false;
	isInteracted = false;
}

// Called when the game starts or when spawned
void ASwitchPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

void ASwitchPuzzle::OnSwitchTarget()
{
	isInteracted = !isInteracted;
	if (TurnOnTargets.Num() != 0)
	{
		for (int8 i = 0; i < TurnOnTargets.Num(); i++)
			Cast<ISwitchable>(TurnOnTargets[i])->OnSwitch();
	}
	if (isClearCheckObject && !isClear)
	{
		isClear = true;
		if (parentRoom->CheckClearList())
		{
			UE_LOG(LogTemp, Warning, TEXT("Room Clear"));
			if (!parentRoom->GetClear())
			{
				parentRoom->SetClear(true);
				UWASaveGame* WASaveGameInstance = Cast<UWASaveGame>(
					UGameplayStatics::LoadGameFromSlot("WASave0", 0));
				APlayerCharacter* pc = NULL;
				UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
				for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
				{
					pc = *iter;
					break;
				}
				if (pc && parentRoom && waInstance)
				{
					WASaveGameInstance->Save(parentRoom->GetRoomSpawnPoint(),
						pc->GetHealthPoint(),
						Cast<ARoomActor>(parentRoom)->GetRoomNumber(),
						waInstance->GetSaveSlotIndex(),
						waInstance->GetCurrentStage());
					Cast<ARoomActor>(parentRoom)->SaveRoom();
				}
			}
		}
	}
	if (isAutoReturnOff && !timerFlag)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle,
			this, &ASwitchPuzzle::OnSwitchTarget, waitForSecond, true);
		SetActorEnableCollision(false);
		timerFlag = true;
	}
	else if (isAutoReturnOff && timerFlag)
	{
		timerFlag = false;
		SetActorEnableCollision(true);
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
}

bool ASwitchPuzzle::IsInteracted()
{
	return isInteracted;
}

void ASwitchPuzzle::SetInteractedFlag(bool value)
{
	isInteracted = value;
}

void ASwitchPuzzle::InitializePuzzle()
{
	ADefaultPuzzle::InitializePuzzle();
	if (initIsTurnOn.Num() != 0)
	{
		for (int8 i = 0; i < TurnOnTargets.Num(); i++)
			Cast<ISwitchable>(TurnOnTargets[i])->SetIsTurnOn(initIsTurnOn[i]);
	}
}