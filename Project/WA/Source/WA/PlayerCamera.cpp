// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"


APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	playerCharacter = nullptr;
	speedLevel = 8.0f;

	defaultRelativeLocation = FVector::ZeroVector;
	defaultRelativeRotation = FRotator::ZeroRotator;

	relativeLocation = FVector::ZeroVector;
	relativeRotation = FRotator::ZeroRotator;
}

void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerCharacter)
	{
		SetActorLocation(FMath::Lerp(
			GetActorLocation(), 
			playerCharacter->GetActorLocation() + relativeLocation, 
			DeltaTime * speedLevel));

		// ȸ�� ���°� �ٸ� ������ ȸ��
		if (GetActorRotation() != relativeRotation)
		{
			SetActorRotation(FMath::Lerp(
				GetActorRotation(),
				relativeRotation,
				DeltaTime * speedLevel));
		}
	}
}

void APlayerCamera::SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	playerCharacter = Player;

	defaultRelativeLocation = RelativeLocation;
	defaultRelativeRotation = RelativeRotation;

	relativeLocation = RelativeLocation;
	relativeRotation = RelativeRotation;
}

void APlayerCamera::ChangeViewport(const FVector& Position, const FRotator& Rotation, bool IsStart)
{
	if (IsStart)
	{
		relativeLocation = Position;
		relativeRotation = Rotation;
	}
	else
	{
		relativeLocation = defaultRelativeLocation;
		relativeRotation = defaultRelativeRotation;
	}
}