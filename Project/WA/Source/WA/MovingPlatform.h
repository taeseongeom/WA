// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switchable.h"
#include "DefaultPuzzle.h"
#include "PlatformWayPoint.h"
#include "MovingPlatform.generated.h"

UCLASS()
class WA_API AMovingPlatform : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
private:
	UPROPERTY(EditAnywhere, Category = "WayPoint")
	APlatformWayPoint* WayPoint;

	UPROPERTY(EditAnywhere, Category = "Init")
	bool initIsTurnOn;

	UPROPERTY(EditAnywhere)
	bool isArrive;

	FTimerHandle CountdownTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void MovePlatform(float DeltaTime);
	void MoveNextWayPoint();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InitializePuzzle() override;
	virtual void OnSwitch() override;
};
