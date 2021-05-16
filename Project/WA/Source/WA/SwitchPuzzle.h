// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "SwitchPuzzle.generated.h"

UCLASS()
class WA_API ASwitchPuzzle : public ADefaultPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchPuzzle();
protected:
	UPROPERTY(EditAnywhere, Category = "SwitchTarget")
		TArray<ADefaultPuzzle*> TurnOnTargets;

	UPROPERTY(EditAnywhere, Category = "SwitchTarget")
		TArray<bool> initIsTurnOn;

	UPROPERTY(EditAnywhere, Category = "Init")
		bool isAutoReturnOff;

	UPROPERTY(EditAnywhere, Category = "Init")
		int16 waitForSecond;

	bool timerFlag;

	FTimerHandle CountdownTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void OnSwitchTarget();
	virtual void BeginPlay() override;
public:
	virtual void InitializePuzzle() override;
};
