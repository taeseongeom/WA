// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinCylinder.h"

ASpinCylinder::ASpinCylinder() {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpinCylinder::BeginPlay()
{
	Super::BeginPlay();
	moveDir = (isTurnLeft) ? -1.0f : 1.0f;
}

void ASpinCylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (puzzleActive)
	{
		AddActorLocalRotation(FRotator(0.0f, turnSpeed * DeltaTime * moveDir, 0.0f));
	}
}

void ASpinCylinder::OnSwitch()
{
	isTurnOn = !isTurnOn;
	puzzleActive = isTurnOn;
}
