// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "CheckRoomClear.h"
#include "SwitchPuzzle.generated.h"

UCLASS()
class WA_API ASwitchPuzzle : public ADefaultPuzzle, public ICheckRoomClear
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

	UPROPERTY()
	bool isInteracted;

	FTimerHandle CountdownTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayEffect();
public:
	virtual void InitializePuzzle() override;
	virtual void OnSwitchTarget();
	virtual bool IsInteracted();
	virtual void SetInteractedFlag(bool value);
};
