// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPuzzle.h"
#include "WA.h"
#include "BreakableBox.h"
#include "RoomActor.h"
#include "UObject/ConstructorHelpers.h"
#include "WAGameModeBase.h"

// Sets default values
ADefaultPuzzle::ADefaultPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initPos = FVector::ZeroVector;
	initRot = FRotator::ZeroRotator;
	static ConstructorHelpers::FObjectFinder<UBlueprint> boxBlueprint(
		TEXT("Blueprint'/Game/BluePrints/Puzzles/BP_BreakableBox.BP_BreakableBox'"));
	if (boxBlueprint.Object)
	{
		breakableBoxBlueprint = (UClass*)boxBlueprint.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ADefaultPuzzle::BeginPlay()
{
	Super::BeginPlay();
	if (isInitBreakableBox)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			breakableBox = World->SpawnActor<ABreakableBox>
				(breakableBoxBlueprint, GetActorLocation(), FRotator::ZeroRotator);

			if (breakableBox != nullptr)
			{
				breakableBox->target = this;
				breakableBox->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				SetActorEnableCollision(false);
				SetHide(true);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Not Init"));
		}
	}
	BeginSetup(GetActorLocation(), GetActorRotation());
	UWAGameInstance* waInstance = Cast<UWAGameInstance>(GetWorld()->GetGameInstance());
	if (UWASaveGame* LoadedGame = Cast<UWASaveGame>(
		UGameplayStatics::LoadGameFromSlot("WASave" + FString::FromInt(waInstance->GetSaveSlotIndex()), 0)))
	{
		LoadedGame->IsStageDatas(waInstance->GetCurrentStage());
		if (!LoadedGame->stageDatas[waInstance->GetCurrentStage()].isOnSwitchs.Contains(GetName()))
		{
			puzzleActive = initpuzzleActive;
		}
	}
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
	if (isInitBreakableBox && breakableBox != nullptr)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(true);
		SetHide(true);
	}
}

bool ADefaultPuzzle::GetPuzzleActive()
{
	return puzzleActive;
}

void ADefaultPuzzle::SetParentRoom(ARoomActor * value)
{
	parentRoom = value;
}
