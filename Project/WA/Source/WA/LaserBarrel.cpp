// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBarrel.h"

#include "Components/LineBatchComponent.h"


ALaserBarrel::ALaserBarrel()
{
 	PrimaryActorTick.bCanEverTick = true;

	damage = 1;
	distance = 3000.0f;

	active = false;
}

void ALaserBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (active)
	{
		FVector laser_start = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f * GetActorScale().Z);
		FVector laser_target_up = laser_start + GetActorForwardVector() * distance;
		FVector laser_target_down = laser_start + (-GetActorForwardVector() * distance);
		FVector laser_target_right = laser_start + GetActorRightVector() * distance;
		FVector laser_target_left = laser_start + (-GetActorRightVector() * distance);

		// 레이저 피격 판정
		{
			bool hit_res;
			FHitResult hit;
			hit_res = GetWorld()->LineTraceSingleByProfile(hit, laser_start, laser_target_up, FName("Laser"));
			if (hit_res)
			{
				if (hit.Actor->ActorHasTag(FName("Character")))
				{
					hit.Actor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
				}
				laser_target_up = hit.Location;
			}
			hit_res = GetWorld()->LineTraceSingleByProfile(hit, laser_start, laser_target_down, FName("Laser"));
			if (hit_res)
			{
				if (hit.Actor->ActorHasTag(FName("Character")))
				{
					hit.Actor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
				}
				laser_target_down = hit.Location;
			}
			hit_res = GetWorld()->LineTraceSingleByProfile(hit, laser_start, laser_target_right, FName("Laser"));
			if (hit_res)
			{
				if (hit.Actor->ActorHasTag(FName("Character")))
				{
					hit.Actor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
				}
				laser_target_right = hit.Location;
			}
			hit_res = GetWorld()->LineTraceSingleByProfile(hit, laser_start, laser_target_left, FName("Laser"));
			if (hit_res)
			{
				if (hit.Actor->ActorHasTag(FName("Character")))
				{
					hit.Actor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
				}
				laser_target_left = hit.Location;
			}
		}
		
		// 레이저 그리기
		{
			GetWorld()->LineBatcher->DrawLine(
				laser_start,
				laser_target_up,
				FColor(92, 158, 255),
				0,
				20.0f,
				1.0f);
			GetWorld()->LineBatcher->DrawLine(
				laser_start,
				laser_target_down,
				FColor(92, 158, 255),
				0,
				20.0f,
				1.0f);
			GetWorld()->LineBatcher->DrawLine(
				laser_start,
				laser_target_right,
				FColor(92, 158, 255),
				0,
				20.0f,
				1.0f);
			GetWorld()->LineBatcher->DrawLine(
				laser_start,
				laser_target_left,
				FColor(92, 158, 255),
				0,
				20.0f,
				1.0f);
		}
	}
}

void ALaserBarrel::SwitchActive(bool IsActive)
{
	active = IsActive;
}