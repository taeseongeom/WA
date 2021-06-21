// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Teleporter.generated.h"

UCLASS()
class WA_API ATeleporter : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:
	virtual void OnSwitch() override;
private:
	void TransferLevel();
private:
	UPROPERTY(EditAnywhere)
	FName TransferLevelName;
	FTimerHandle CountdownTimerHandle;
};
