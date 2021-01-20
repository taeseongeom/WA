// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.h"
#include "Shot.generated.h"

UCLASS()
class WA_API AShot : public AActor, public IPuzzleObject
{
	GENERATED_BODY()
	
public:	
	AShot();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Be excuted by pressing interaction key.
	UFUNCTION()
	virtual void Interaction() override;
};
