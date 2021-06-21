// Fill out your copyright notice in the Description page of Project Settings.


#include "PointBox.h"
#include "Components/BillboardComponent.h"

// Sets default values
APointBox::APointBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APointBox::BeginPlay()
{
	Super::BeginPlay();
	teleportPoint = FindComponentByClass<UBillboardComponent>();
	initTeleportPos = teleportPoint->GetComponentLocation();
}

void APointBox::Teleport()
{
	FVector tempVector = GetActorLocation();
	SetActorLocation(teleportPoint->GetComponentLocation());
	teleportPoint->SetWorldLocation(tempVector);
}

void APointBox::OnSwitch()
{
	Teleport();
}

void APointBox::InitializePuzzle()
{
	if (teleportPoint->GetComponentLocation() != initTeleportPos)
		Teleport();
	Super::InitializePuzzle();
}
