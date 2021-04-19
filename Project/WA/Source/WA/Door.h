// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class WA_API ADoor : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
public:
	ADoor();
protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
protected:
	virtual void BeginSetup(FVector pos, FRotator rot) override;
public:
	virtual void InitializePuzzle() override;
	virtual void OnSwitch() override;
private:
	class UBillboardComponent* spawnPoint;
};
