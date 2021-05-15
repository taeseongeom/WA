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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnSwitch() override;

private:
	UPROPERTY(EditAnywhere, Category = "Laser")
	int damage;
};
