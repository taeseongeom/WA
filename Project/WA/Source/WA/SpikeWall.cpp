// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeWall.h"


ASpikeWall::ASpikeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	damage = 1;

	startPos = FVector::ZeroVector;
	targetPos = FVector::ZeroVector;
	curTime = 0;
	travelTime = 0;
}

void ASpikeWall::BeginPlay()
{
	Super::BeginPlay();

	wallFactors = GetComponentsByTag(UActorComponent::StaticClass(), FName("SpikeBody"));

	int32 index = FMath::RandRange(0, (wallFactors.Num() / 3) - 1);
	RemoveTile(index);
}

void ASpikeWall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->ActorHasTag(FName("Character")))
		OtherActor->TakeDamage(damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
}

void ASpikeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!targetPos.IsZero())
	{
		curTime += DeltaTime;

		if (curTime < travelTime)
			SetActorLocation(FMath::Lerp<FVector>(startPos, targetPos, curTime / travelTime));
		else
			Destroy();
	}
}

void ASpikeWall::RemoveTile(int32 TileIndex)
{
	if (TileIndex < wallFactors.Num())
	{
		int32 i = TileIndex * 3;
		wallFactors[i + 0]->DestroyComponent();
		wallFactors[i + 1]->DestroyComponent();
		wallFactors[i + 2]->DestroyComponent();
	}
		
}

void ASpikeWall::MoveTo(const FVector& Destination, float TravelTime)
{
	startPos = GetActorLocation();
	targetPos = Destination;
	curTime = 0;
	travelTime = TravelTime;
}