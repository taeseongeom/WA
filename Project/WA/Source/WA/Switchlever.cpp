// Fill out your copyright notice in the Description page of Project Settings.


#include "Switchlever.h"
#include "PlayerCharacter.h"
#include "Switchable.h"
#include "Runtime/Engine/Public/EngineUtils.h"

// Sets default values
ASwitchlever::ASwitchlever() : ASwitchPuzzle(){ }

// Called when the game starts or when spawned
void ASwitchlever::BeginPlay()
{
	ADefaultPuzzle::BeginPlay();
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
}

void ASwitchlever::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(true);
		Cast<APlayerCharacter>(OtherActor)->DisplayInteractionUI(true);
	}
}

void ASwitchlever::NotifyActorEndOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
		Cast<APlayerCharacter>(OtherActor)->DisplayInteractionUI(false);
	}
}

void ASwitchlever::Interact()
{
	if (IsInteractable()) // Interact Begin
	{
		PlayEffect();
		OnSwitchTarget();
	}
}