#include "Door.h"
#include "Components/BillboardComponent.h"

ADoor::ADoor() : ADefaultPuzzle() {
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	spawnPoint = FindComponentByClass<UBillboardComponent>();
}

void ADoor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (puzzleActive)
	{
		OtherActor->SetActorLocation(spawnPoint->GetComponentLocation());
	}
}

void ADoor::BeginSetup(FVector pos, FRotator rot)
{
	Super::BeginSetup(pos, rot);
}

void ADoor::InitializePuzzle()
{
	Super::InitializePuzzle();
}

void ADoor::OnSwitch()
{
	if (isTurnOn)
	{
		isTurnOn = false;
	}
	else
	{
		isTurnOn = true;
		UE_LOG(LogTemp, Warning, TEXT("OpenDoor"));
	}
	puzzleActive = isTurnOn;
}
