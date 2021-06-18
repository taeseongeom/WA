// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Laser.generated.h"

UCLASS()
class WA_API ALaser : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	ALaser();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnSwitch() override;

private:
	// The lasers damage per hit.
	UPROPERTY(EditAnywhere, Category = "Laser")
	int damage;
	// The length of laser.
	UPROPERTY(EditAnywhere, Category = "Laser")
	float distance;
};
