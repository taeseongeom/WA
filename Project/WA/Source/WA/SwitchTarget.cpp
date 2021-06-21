// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchTarget.h"

// Sets default values
ASwitchTarget::ASwitchTarget() : ASwitchPuzzle() { }

// Called when the game starts or when spawned
void ASwitchTarget::BeginPlay()
{
	ADefaultPuzzle::BeginPlay();
}

void ASwitchTarget::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Bullet")))
	{
		PlayEffect();
		OnSwitchTarget();
	}
}