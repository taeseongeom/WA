// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleObject.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include <DrawDebugHelpers.h>

#include "PlayerPawn.h"

// Sets default values
APuzzleObject::APuzzleObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxExtent = FVector(100, 100, 50);

	isShow = false;


	velocity = velocity.ZeroVector;

	jumping = true;

	num_overlappingObj = 0;
}

// Called when the game starts or when spawned
void APuzzleObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_Player != nullptr)
	{
		m_Player->InteractionWithPuzzle.AddUFunction(this, FName("Interaction"));
	}
}

// Called every frame
void APuzzleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (velocity * DeltaTime));

	if (jumping)
	{
		velocity.Z -= 5.f;
	}


	if (isShow)
	{
		DrawDebugBox(GetWorld(), GetActorLocation(), boxExtent, FColor(180, 0, 0), false, 0, 0, 1);
	}
}

// Called to bind functionality to input
void APuzzleObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APuzzleObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	num_overlappingObj++;

	if (OtherActor->GetActorLocation().Z < GetActorLocation().Z)
	{
		jumping = false;
	}

	velocity.Z = 0;
}

void APuzzleObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	num_overlappingObj--;

	if (num_overlappingObj < 1)
	{
		jumping = true;
	}
}


void APuzzleObject::Interaction()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("PuzzleObject: Interaction Key is pressed."));
}