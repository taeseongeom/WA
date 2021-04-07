// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Initializable.h"
#include "Switchable.h"
#include "DirectionChanger.generated.h"

UCLASS()
class WA_API ADirectionChanger : public AActor, public IInitializable, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	ADirectionChanger();

private:
	UPROPERTY(EditAnywhere, Category = "Time")
	float revealTime;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	bool isCounterclockwise;

	float currentTick;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InitializePuzzle(int room_number) override;
	virtual void OnSwitch() override;
};
