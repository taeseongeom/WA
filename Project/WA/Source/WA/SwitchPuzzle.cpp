// Fill out your copyright notice in the Description page of Project Settings.
#include "SwitchPuzzle.h"
#include "Switchable.h"
#include "WA.h"

// Sets default values
ASwitchPuzzle::ASwitchPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	timerFlag = false;
}

// Called when the game starts or when spawned
void ASwitchPuzzle::BeginPlay()
{
	Super::BeginPlay();
	BeginSetup(GetActorLocation(), GetActorRotation());
}

void ASwitchPuzzle::OnSwitchTarget()
{
	for (int8 i = 0; i < TurnOnTargets.Num(); i++)
		Cast<ISwitchable>(TurnOnTargets[i])->OnSwitch();
	if (isAutoReturnOff && !timerFlag)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle,
			this, &ASwitchPuzzle::OnSwitchTarget, waitForSecond, true);
		SetActorEnableCollision(false);
		timerFlag = true;
	}
	else if (isAutoReturnOff && timerFlag)
	{
		timerFlag = false;
		SetActorEnableCollision(true);
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
}

void ASwitchPuzzle::InitializePuzzle()
{
	ADefaultPuzzle::InitializePuzzle();
	for (int8 i = 0; i < TurnOnTargets.Num(); i++)
		Cast<ISwitchable>(TurnOnTargets[i])->SetIsTurnOn(initIsTurnOn[i]);
}
