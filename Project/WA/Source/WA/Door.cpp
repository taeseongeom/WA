#include "Door.h"
#include "Components/BillboardComponent.h"
#include "RoomActor.h"
#include "WA.h"
#include "PlayerCharacter.h"
#include "WAGameModeBase.h"

ADoor::ADoor() : ADefaultPuzzle() {
}
void ADoor::BeginPlay()
{
	Super::BeginPlay();                                                    
	isClear = false;
	if (!isClearCheckObject)
		isClear = true;
	spawnPoint = FindComponentByClass<UBillboardComponent>();
}
void ADoor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (puzzleActive && OtherActor->ActorHasTag(FName("Character")))
	{
		audioComp->Play();
		if (isClearCheckObject && !isClear)
		{
			isClear = true;
		}
		if (parentRoom->CheckClearList())
		{
			UE_LOG(LogTemp, Warning, TEXT("Room Clear"));
			if (!parentRoom->GetClear())
			{
				parentRoom->SetClear(true);
				UE_LOG(LogTemp, Warning, TEXT("Not saved"));
				APlayerCharacter* pc = NULL;
				for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
				{
					pc = *iter;
					break;
				}
				UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
				UWASaveGame* waSave = Cast<UWASaveGame>(
					UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0));
				if (pc && parentRoom && waInstance)
				{
					UE_LOG(LogTemp, Warning, TEXT("Save"));
					waSave->Save(spawnPoint->GetComponentLocation(),
						pc->GetHealthPoint(),
						TransferRoomNumber,
						waInstance->GetSaveSlotIndex(),
						waInstance->GetCurrentStage());
					Cast<ARoomActor>(parentRoom)->SaveRoom();
				}
			}
		}
		AWAGameModeBase* WaGMB = (AWAGameModeBase*)(GetWorld()->GetAuthGameMode());
		OtherActor->SetActorLocation(spawnPoint->GetComponentLocation());
		WaGMB->SetRoomSpawnPoint(TransferRoomNumber, spawnPoint->GetComponentLocation());
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
	}
	puzzleActive = isTurnOn;
}