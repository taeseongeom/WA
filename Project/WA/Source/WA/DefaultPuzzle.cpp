// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPuzzle.h"
#include "WA.h"
#include "WAGameModeBase.h"

// Sets default values
ADefaultPuzzle::ADefaultPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initPos = FVector::ZeroVector;
	initRot = FRotator::ZeroRotator;
}

// Called when the game starts or when spawned
void ADefaultPuzzle::BeginPlay()
{
	Super::BeginPlay();
	puzzleActive = initpuzzleActive;
	BeginSetup(GetActorLocation(), GetActorRotation());
	((AWAGameModeBase*)(GetWorld()->GetAuthGameMode()))->AddInitPuzzle(this, roomNum);
}

// Called every frame
void ADefaultPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultPuzzle::BeginSetup(FVector pos, FRotator rot)
{
	initPos = pos;
	initRot = rot;
}

void ADefaultPuzzle::InitializePuzzle()
{
	SetActorLocation(initPos);
	SetActorRotation(initRot);
	puzzleActive = initpuzzleActive;
}