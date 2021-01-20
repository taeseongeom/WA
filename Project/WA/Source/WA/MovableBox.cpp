// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableBox.h"
#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AMovableBox::AMovableBox()
{
 	PrimaryActorTick.bCanEverTick = true;

	isShow = false;


	velocity = velocity.ZeroVector;

	jumping = true;

	num_overlappingObj = 0;
}

void AMovableBox::BeginPlay()
{
	Super::BeginPlay();
	
	boxExtent = Cast<UBoxComponent>(GetComponentsByTag(UBoxComponent::StaticClass(), FName("Interaction Region"))[0])->GetScaledBoxExtent();

	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interaction"));
		break;
	}
}

void AMovableBox::NotifyActorBeginOverlap(AActor* OtherActor)
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
void AMovableBox::NotifyActorEndOverlap(AActor* OtherActor)
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

void AMovableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovableBox::Interaction()
{
	if (isInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Blue, GetName() + ": Interaction");
	}
}