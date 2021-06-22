// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionChanger.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Components/ArrowComponent.h"


ADirectionChanger::ADirectionChanger()
{
 	PrimaryActorTick.bCanEverTick = true;

	changeActive = true;

	revealTime = 3.0f;
	isCounterclockwise = false;

	activeColor = FColor::Green;
	deactiveColor = FColor::Red;

	arrowMesh = nullptr;

	currentTick = 0.0f;
}

void ADirectionChanger::BeginPlay()
{
	Super::BeginPlay();

	BeginSetup(GetActorLocation(), GetActorRotation());

	arrowMesh = Cast<UArrowComponent>(GetComponentByClass(UArrowComponent::StaticClass()));
}

void ADirectionChanger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (changeActive)
	{
		if (OtherActor->ActorHasTag(FName("Bullet")))
		{
			OtherActor->SetActorRotation(GetActorRotation());
			OtherActor->SetActorLocation(FVector(
				GetActorLocation().X,
				GetActorLocation().Y,
				OtherActor->GetActorLocation().Z));

			changeActive = false;
			arrowMesh->SetArrowColor(FLinearColor(deactiveColor));
		}
	}
}

void ADirectionChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!changeActive)
	{
		currentTick += DeltaTime;
		
		if (currentTick >= revealTime)
		{
			currentTick = 0.0f;
			changeActive = true;
			arrowMesh->SetArrowColor(FLinearColor(activeColor));
		}
	}
}

void ADirectionChanger::InitializePuzzle()
{
	Super::InitializePuzzle();

	currentTick = 0.0f;
}

void ADirectionChanger::OnSwitch()
{
	FRotator rot = FRotator(0.0f, 45.0f, 0.0f);
	if (isCounterclockwise)
	{
		rot *= -1.0f;
	}
	
	SetActorRotation(GetActorRotation() + rot);
}