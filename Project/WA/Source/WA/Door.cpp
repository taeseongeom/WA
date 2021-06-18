#include "Door.h"
#include "Components/BillboardComponent.h"
#include "WAGameModeBase.h"

ADoor::ADoor() : ADefaultPuzzle() {
}
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	spawnPoint = FindComponentByClass<UBillboardComponent>();
}
void ADoor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (puzzleActive && OtherActor->ActorHasTag(FName("Character")))
	{
		AWAGameModeBase* WaGMB = (AWAGameModeBase*)(GetWorld()->GetAuthGameMode());
		OtherActor->SetActorLocation(spawnPoint->GetComponentLocation());
		WaGMB->ChangeRoom(TransferRoomNumber, spawnPoint->GetComponentLocation());
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