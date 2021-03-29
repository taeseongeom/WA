// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "PlayerCharacter.h"
#include "Shooter_Bullet.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AShooter::AShooter()
{
 	PrimaryActorTick.bCanEverTick = false;

	SetInteractability(false);
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
		iter->BeginInteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		iter->EndInteractionWithPuzzle.AddUFunction(this, FName("Interacted"));
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

void AShooter::Interact()
{
	if (IsInteractable()) // Interact Begin
	{
		puzzleActive = !puzzleActive;
		pc->SetInteractObject(this);
		pc->SetCharacterState(ECharacterState::Shooting);
	}
}

void AShooter::Interacted()
{
	if (puzzleActive)
	{
		puzzleActive = !puzzleActive;
		pc->SetCharacterState(ECharacterState::Idle);
		pc->ClearInteractObject();
		AShooter_Bullet* bullet = (AShooter_Bullet*)GetWorld()->SpawnActor<AActor>(BulletBlueprint, GetActorLocation(), GetActorRotation());
		bullet->SetStack(BulletSpeed, Crash_count);
	}
}