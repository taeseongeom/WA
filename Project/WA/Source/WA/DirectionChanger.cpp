// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionChanger.h"
#include "PlayerCharacter.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


ADirectionChanger::ADirectionChanger()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetInteractability(false);
}

void ADirectionChanger::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
}

void ADirectionChanger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(true);
	}
}
void ADirectionChanger::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
	}
}

void ADirectionChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADirectionChanger::InitializePuzzle(int room_number)
{
	if (roomNum == room_number)
	{

	}
}

void ADirectionChanger::Interact()
{
	if (IsInteractable())
	{

	}
}

void ADirectionChanger::OnSwitch()
{

}