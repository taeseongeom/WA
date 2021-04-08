// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformWayPoint.generated.h"

UCLASS()
class WA_API APlatformWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformWayPoint();

	UPROPERTY(EditAnywhere, Category = "WayPoint")
	APlatformWayPoint* NextPoint;
	UPROPERTY(EditAnywhere, Category = "WayPoint")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "WayPoint")
	float DelayTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	APlatformWayPoint* SwitchPlatformWayPoint();
	float GetSpeed();
	float GetDelayTime();
};
