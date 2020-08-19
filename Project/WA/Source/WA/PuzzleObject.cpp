// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleObject.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
APuzzleObject::APuzzleObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxExtent = FVector(100, 100, 50);
}

// Called when the game starts or when spawned
void APuzzleObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzleObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}


void APuzzleObject::Interaction()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("PuzzleObject: Interaction Key is pressed."));
}