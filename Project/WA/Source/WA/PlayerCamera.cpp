// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"


APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	player_character = nullptr;
	speed_level = 8.0f;

	relative_location = FVector::ZeroVector;
}

void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player_character)
	{
		FVector target_pos = player_character->GetActorLocation();
		target_pos.X += relative_location.X;
		target_pos.Z = GetActorLocation().Z;

		SetActorLocation(FMath::Lerp(GetActorLocation(), target_pos, DeltaTime * speed_level));
	}
}

void APlayerCamera::SetInitialize(AActor* Player, FVector RelativeLocation)
{
	player_character = Player;
	relative_location = RelativeLocation;
}