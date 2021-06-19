// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeWall.generated.h"

UCLASS()
class WA_API ASpikeWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpikeWall();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	int damage;

	FVector startPos;
	FVector targetPos;
	float curTime;
	float travelTime;

	TArray<UActorComponent*> wallFactors;


	void RemoveTile(int32 TileIndex);

public:
	void MoveTo(const FVector& Destination, float TravelTime);
};
