// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingBomb.h"

#include "PlayerCharacter.h"


AJumpingBomb::AJumpingBomb()
{
 	PrimaryActorTick.bCanEverTick = true;

	bombEffect = nullptr;

	jumpHeight = 500.0f;

	playerCharacter = nullptr;
	startPos = FVector::ZeroVector;
	targetPos = FVector::ZeroVector;
	curTime = 0;
	travelTime = 0;

	jumpCount = 0;
}

void AJumpingBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumpCount > 0)
	{
		curTime += DeltaTime;

		float rate = curTime / travelTime;
		if (rate >= 1)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), bombSound);
			GetWorld()->SpawnActor<AActor>(bombEffect, targetPos, FRotator::ZeroRotator);
			startPos = targetPos;
			targetPos = playerCharacter->GetActorLocation();
			targetPos.Z = 0;
			curTime = 0;

			jumpCount--;
		}

		SetActorLocation(FMath::Lerp<FVector>(startPos, targetPos, rate) + FVector(0, 0, FMath::Sin(PI * rate)) * jumpHeight);
	}
	else
	{
		Destroy();
	}
}

void AJumpingBomb::FireBomb(APlayerCharacter* PlayerCharacter, float TravelTime, int32 JumpCount)
{
	playerCharacter = PlayerCharacter;
	travelTime = TravelTime;
	jumpCount = JumpCount;

	startPos = GetActorLocation();
	targetPos = playerCharacter->GetActorLocation();
	targetPos.Z = 0;
	curTime = 0;
}