// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEntranceTrigger.h"

#include "Boss_Stage2.h"

#include "Components/BillboardComponent.h"


ABossEntranceTrigger::ABossEntranceTrigger()
{
 	PrimaryActorTick.bCanEverTick = true;

	platformToRemove = nullptr;
	bossCharacter = nullptr;

	delay = 0;
}

void ABossEntranceTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ABossEntranceTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->ActorHasTag(FName("Character")))
	{
		if (!puzzleActive && delay <= 0)
		{
			check(platformToRemove || bossCharacter);
			
			platformToRemove->SetActorHiddenInGame(true);
			platformToRemove->SetActorEnableCollision(false);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);

			bossCharacter->Activate();
			
			puzzleActive = true;
		}
	}
}

void ABossEntranceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (delay > 0)
		delay -= DeltaTime;
}

void ABossEntranceTrigger::InitializePuzzle()
{
	delay = 1.0f;
	
	Super::InitializePuzzle();

	platformToRemove->SetActorHiddenInGame(false);
	platformToRemove->SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	bossCharacter->Initialize();
}