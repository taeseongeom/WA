// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.h"
#include "Shooter.generated.h"

UCLASS()
class WA_API AShooter : public AActor, public IPuzzleObject
{
	GENERATED_BODY()
	
public:	
	AShooter();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
