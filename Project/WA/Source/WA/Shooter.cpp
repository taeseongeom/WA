// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "PlayerCharacter.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AShooter::AShooter()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetInteractability(false);
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
}

void AShooter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(true);
	}
}
void AShooter::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
	}
}

void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooter::Interact()
{
	if (IsInteractable())
	{

	}
}