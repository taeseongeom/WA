// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include "Components/LineBatchComponent.h"

ALaser::ALaser()
{
 	PrimaryActorTick.bCanEverTick = true;

	damage = 1;
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (puzzleActive && !IsHidden())
	{
		FVector laser_start = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
		FVector laser_target = laser_start + GetActorForwardVector() * 10000.0f;

		FHitResult hit;
		//bool hit_res = GetWorld()->LineTraceSingleByChannel(hit, laser_start, laser_target, ECollisionChannel::ECC_GameTraceChannel3);
		bool hit_res = GetWorld()->LineTraceSingleByProfile(hit, laser_start, laser_target, FName("Laser"));
		if (hit_res)
		{
			if (hit.Actor->ActorHasTag(FName("Character")))
			{
				hit.Actor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
			}

			laser_target = hit.Location;
		}

		GetWorld()->LineBatcher->DrawLine(
			laser_start,
			laser_target,
			FColor(92, 158, 255),
			0,
			20.0f,
			1.0f
		);
	}
}

void ALaser::OnSwitch()
{
	puzzleActive = !puzzleActive;
}