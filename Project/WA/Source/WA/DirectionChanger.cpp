// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionChanger.h"
#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


ADirectionChanger::ADirectionChanger()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ADirectionChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADirectionChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADirectionChanger::Interaction()
{
	if (isInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Blue, GetName() + ": Interaction");
	}
}