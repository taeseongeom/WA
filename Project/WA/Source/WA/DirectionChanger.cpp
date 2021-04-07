// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionChanger.h"
#include "PlayerCharacter.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


ADirectionChanger::ADirectionChanger()
{
 	PrimaryActorTick.bCanEverTick = true;

	puzzleActive = true;

	revealTime = 3.0f;
	isCounterclockwise = false;

	currentTick = 0.0f;
}

void ADirectionChanger::BeginPlay()
{
	Super::BeginPlay();

	BeginSetup(GetActorLocation(), GetActorRotation());
}

void ADirectionChanger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (puzzleActive)
	{
		if (OtherActor->ActorHasTag(FName("Bullet")))
		{
			OtherActor->SetActorRotation(GetActorRotation());
			OtherActor->SetActorLocation(FVector(
				GetActorLocation().X,
				GetActorLocation().Y,
				OtherActor->GetActorLocation().Z));

			puzzleActive = false;
		}
	}
}

void ADirectionChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!puzzleActive)
	{
		currentTick += DeltaTime;
		
		if (currentTick >= revealTime)
		{
			currentTick = 0.0f;
			puzzleActive = true;
		}
	}
}

void ADirectionChanger::InitializePuzzle(int room_number)
{
	if (roomNum == room_number)
	{
		puzzleActive = true;
		SetActorLocation(GetInitPos());
		SetActorRotation(GetInitRot());

		currentTick = 0.0f;
	}
}

void ADirectionChanger::OnSwitch()
{
	FRotator rot = FRotator(0.0f, 45.0f, 0.0f);
	if (isCounterclockwise)
	{
		rot *= -1.0f;
	}
	
	SetActorRotation(GetActorRotation() + rot);
}