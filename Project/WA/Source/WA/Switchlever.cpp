// Fill out your copyright notice in the Description page of Project Settings.


#include "Switchlever.h"
#include "PlayerCharacter.h"
#include "Switchable.h"
#include "Runtime/Engine/Public/EngineUtils.h"

// Sets default values
ASwitchlever::ASwitchlever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASwitchlever::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
	BeginSetup(GetActorLocation(), GetActorRotation());
}

void ASwitchlever::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Switch"));
		SetInteractability(true);
	}
}

void ASwitchlever::NotifyActorEndOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
	}
}

void ASwitchlever::Interact()
{
	if (IsInteractable()) // Interact Begin
	{
		for (int8 i = 0; i < TurnOnTargets.Num(); i++)
			Cast<ISwitchable>(TurnOnTargets[i])->OnSwitch();
	}
}

void ASwitchlever::InitializePuzzle()
{
	Super::InitializePuzzle();
	for (int8 i = 0; i < TurnOnTargets.Num(); i++)
		Cast<ISwitchable>(TurnOnTargets[i])->SetIsTurnOn(initIsTurnOn[i]);
}
