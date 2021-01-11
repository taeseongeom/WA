// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleObject.h"
#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


APuzzleObject::APuzzleObject()
{
 	PrimaryActorTick.bCanEverTick = true;

	isShow = false;


	velocity = velocity.ZeroVector;

	jumping = true;

	num_overlappingObj = 0;
}

void APuzzleObject::BeginPlay()
{
	Super::BeginPlay();

	boxExtent = Cast<UBoxComponent>(GetComponentsByTag(UBoxComponent::StaticClass(), FName("Interaction Region"))[0])->GetScaledBoxExtent();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interaction"));
		break;
	}
}

void APuzzleObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	num_overlappingObj++;

	if (OtherActor->GetActorLocation().Z < GetActorLocation().Z)
	{
		jumping = false;
	}

	velocity.Z = 0;


	if (OtherActor->ActorHasTag(FName("Character")))
	{
		isInteractable = true;
	}
}
void APuzzleObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	num_overlappingObj--;

	if (num_overlappingObj < 1)
	{
		jumping = true;
	}


	if (OtherActor->ActorHasTag(FName("Character")))
	{
		isInteractable = false;
	}
}

void APuzzleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (velocity * DeltaTime));

	if (jumping)
	{
		velocity.Z -= 5.f;
	}


	if (isShow)
	{
		DrawDebugBox(GetWorld(), GetActorLocation(), boxExtent, FColor(180, 0, 0), false, 0, 0, 1);
	}
}


void APuzzleObject::Interaction()
{
	if (isInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Blue, GetName() + ": Interaction");
	}
}