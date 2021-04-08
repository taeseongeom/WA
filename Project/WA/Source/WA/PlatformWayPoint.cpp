// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformWayPoint.h"

// Sets default values
APlatformWayPoint::APlatformWayPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlatformWayPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformWayPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

APlatformWayPoint * APlatformWayPoint::SwitchPlatformWayPoint()
{
	return NextPoint;
}

float APlatformWayPoint::GetSpeed()
{
	return Speed;
}

float APlatformWayPoint::GetDelayTime()
{
	return DelayTime;
}

