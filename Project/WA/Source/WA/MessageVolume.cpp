// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageVolume.h"

#include "PlayerCharacter.h"


AMessageVolume::AMessageVolume()
{
 	PrimaryActorTick.bCanEverTick = false;

	isUsed = false;

	message = "Input message here!";
	exposureTime = 0.0f;
}

void AMessageVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AMessageVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!isUsed && OtherActor->ActorHasTag(FName("Character")))
	{
		APlayerCharacter* pc = Cast<APlayerCharacter>(OtherActor);
		if (pc)
		{
			isUsed = true;

			pc->DisplayMessage(message, exposureTime);
		}
	}
}

