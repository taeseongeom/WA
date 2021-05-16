// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakableBox.h"
#include "DefaultPuzzle.h"

// Sets default values
ABreakableBox::ABreakableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABreakableBox::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Create Box"));
}

void ABreakableBox::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Bullet")))
	{
		target->SetHide(false);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		target->SetActorEnableCollision(true);
	}
}

