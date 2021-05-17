// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewportChanger.h"

#include "PlayerCharacter.h"
#include "PlayerCamera.h"


AViewportChanger::AViewportChanger()
{
 	PrimaryActorTick.bCanEverTick = false;

	cameraPos = FVector::ZeroVector;
	cameraRot = FRotator::ZeroRotator;
}

void AViewportChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AViewportChanger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		Cast<APlayerCharacter>(OtherActor)->GetPlayerCamera()->ChangeViewport(cameraPos, cameraRot, true);
	}
}
void AViewportChanger::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		Cast<APlayerCharacter>(OtherActor)->GetPlayerCamera()->ChangeViewport(cameraPos, cameraRot, false);
	}
}