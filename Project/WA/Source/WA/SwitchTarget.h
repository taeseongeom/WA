// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchPuzzle.h"
#include "SwitchTarget.generated.h"

UCLASS()
class WA_API ASwitchTarget : public ASwitchPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
public:
};
