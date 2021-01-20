// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot.h"
#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AShot::AShot()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AShot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShot::Interaction()
{
	if (isInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Blue, GetName() + ": Interaction");
	}
}