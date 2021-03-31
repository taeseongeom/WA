// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.h"
#include "DirectionChanger.generated.h"

UCLASS()
class WA_API ADirectionChanger : public AActor, public IPuzzleObject
{
	GENERATED_BODY()
	
public:	
	ADirectionChanger();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
