// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPuzzle.h"
#include "WA.h"
#include "RoomActor.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "WAGameModeBase.h"


ADefaultPuzzle::ADefaultPuzzle()
{
 	PrimaryActorTick.bCanEverTick = true;
	initPos = FVector::ZeroVector;
	initRot = FRotator::ZeroRotator;
}

void ADefaultPuzzle::BeginPlay()
{
	Super::BeginPlay();
	BeginSetup(GetActorLocation(), GetActorRotation());
	UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
	if (UWASaveGame* LoadedGame = Cast<UWASaveGame>(
		UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0)))
	{
		LoadedGame->IsStageDatas(waInstance->GetCurrentStage());
		if (!LoadedGame->stageDatas[waInstance->GetCurrentStage()].isOnSwitchs.Contains(GetName()))
		{
			puzzleActive = initpuzzleActive;
		}
	}
	audioComp = FindComponentByClass<UAudioComponent>();
	if (audioComp)
	{
		audioComp->bAutoActivate = false;
		if (effects.Num() > 0)
			audioComp->SetSound(effects[0]);
	}
	BeginSetup(GetActorLocation(), GetActorRotation());
	((AWAGameModeBase*)(GetWorld()->GetAuthGameMode()))->AddInitPuzzle(this, roomNum);
}

void ADefaultPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultPuzzle::BeginSetup(FVector pos, FRotator rot)
{
	initPos = pos;
	initRot = rot;
}

void ADefaultPuzzle::InitializePuzzle()
{
	SetActorLocation(initPos);
	SetActorRotation(initRot);
	puzzleActive = initpuzzleActive;
}

bool ADefaultPuzzle::GetPuzzleActive()
{
	return puzzleActive;
}

void ADefaultPuzzle::SetParentRoom(ARoomActor * value)
{
	parentRoom = value;
}
