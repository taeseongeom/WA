// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "PointBox.generated.h"

UCLASS()
class WA_API APointBox : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointBox();
private:
	void Teleport();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnSwitch() override;
	virtual void InitializePuzzle() override;
private:
	FVector initTeleportPos;

	class UBillboardComponent* teleportPoint;
};
