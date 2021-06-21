// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "WA.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	SetActorEnableCollision(false);
	pController = GetWorld()->GetFirstPlayerController();
	pController->ClientSetCameraFade(true, FColor::Black, FVector2D(1.0, 0.0), 0.7);
}

void ATeleporter::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (puzzleActive && OtherActor->ActorHasTag(FName("Character")))
	{
		UWASaveGame* waSave = Cast<UWASaveGame>(
			UGameplayStatics::LoadGameFromSlot("WASave0", 0));
		UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
		if (waInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save"));
			waSave->Save(FVector(0, 0, 0),
				3,
				1,
				waInstance->GetSaveSlotIndex(),
				waInstance->GetCurrentStage() +1);
		}
		pController->ClientSetCameraFade(true, FColor::Black, FVector2D(0.0, 1.0), 0.7);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle,
			this, &ATeleporter::TransferLevel, 0.7, true);
	}
}

void ATeleporter::OnSwitch()
{
	if (isTurnOn)
	{
		isTurnOn = false;
		SetActorEnableCollision(false);
	}
	else
	{
		isTurnOn = true;
		UE_LOG(LogTemp, Warning, TEXT("OpenTeleporter"));
		SetActorEnableCollision(true);
	}
	puzzleActive = isTurnOn;
}

void ATeleporter::TransferLevel()
{
	UGameplayStatics::OpenLevel(this, TransferLevelName);
}
