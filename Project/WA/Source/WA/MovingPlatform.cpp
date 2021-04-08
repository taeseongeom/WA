// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "WA.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isArrive = false;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (!isArrive)
	{
		SetActorLocation(GetActorLocation() +
			(WayPoint->GetActorLocation() - GetActorLocation()).GetSafeNormal()
			* DeltaTime * WayPoint->GetSpeed());
	}
	if (FVector::Distance(GetActorLocation(), WayPoint->GetActorLocation()) < 1.5f && !isArrive)
	{
		isArrive = true;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle,
			this, &AMovingPlatform::MoveNextWayPoint, WayPoint->GetDelayTime(), true);
	}
}

void AMovingPlatform::MoveNextWayPoint()
{
	UE_LOG(LogTemp, Warning, TEXT("switch"));
	WayPoint = WayPoint->SwitchPlatformWayPoint();
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	isArrive = false;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isTurnOn) MovePlatform(DeltaTime);
}

void AMovingPlatform::InitializePuzzle(int room_number)
{
}

void AMovingPlatform::TurnOnAndOffPlatform(bool value)
{
	isTurnOn = value;
}

