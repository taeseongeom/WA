// Fill out your copyright notice in the Description page of Project Settings.


#include "Spike.h"

ASpike::ASpike()
{
 	PrimaryActorTick.bCanEverTick = true;

	damage = 1;
	spikeType = ESpikeType::FIXED;
	beginDelay = 0.0f;
	activePeriod = 1.0f;
	deactivePeriod = 1.0f;

	activation = false;

	isBegin = true;
	currentTime = 0.0f;

	playAnimation = false;
	animationTime = 0.0f;

	spikeMesh = nullptr;
}

void ASpike::BeginPlay()
{
	Super::BeginPlay();
	
	spikeMesh = Cast<USceneComponent>(GetComponentsByTag(USceneComponent::StaticClass(), FName("SpikeMesh"))[0]);

	if (ESpikeType::FIXED == spikeType)
	{
		puzzleActive = true;
	}
	SwitchActive(puzzleActive);
}

void ASpike::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (activation)
	{
		if (OtherActor->ActorHasTag(FName("Character")))
		{
			OtherActor->TakeDamage((float)damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
		}
	}
}

void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 시간경과 타입의 가시 - 시간에 따른 상태변화
	if (ESpikeType::TIMELAPSE == spikeType && !IsHidden())
	{
		currentTime += DeltaTime;

		if (isBegin)
		{
			if (currentTime >= beginDelay)
			{
				currentTime = 0.0f;
				isBegin = false;
			}
		}
		else
		{
			if (activation)
			{
				if (currentTime >= activePeriod)
				{
					currentTime = 0.0f;
					SwitchActive(false);
				}
			}
			else
			{
				if (currentTime >= deactivePeriod)
				{
					currentTime = 0.0f;
					SwitchActive(true);
				}
			}
		}
	}

	// 가시 상태변화 애니메이션
	if (playAnimation)
	{
		if (activation)
		{
			spikeMesh->SetRelativeLocation(FMath::Lerp(spikeMesh->GetRelativeLocation(), FVector(0.0f, 0.0f, 0.0f), DeltaTime * 10.0f));

			if (spikeMesh->GetRelativeLocation() == FVector(0.0f, 0.0f, 0.0f))
			{
				playAnimation = false;
			}
		}
		else
		{
			spikeMesh->SetRelativeLocation(FMath::Lerp(spikeMesh->GetRelativeLocation(), FVector(0.0f, 0.0f, -100.0f), DeltaTime * 10.0f));

			if (spikeMesh->GetRelativeLocation() == FVector(0.0f, 0.0f, 0.0f))
			{
				playAnimation = true;
			}
		}
	}
}

void ASpike::OnSwitch()
{
	if (ESpikeType::SWITCHABLE == spikeType)
	{
		// 현재 스위치를 조작할 때마다 상태 변경
		SwitchActive(!puzzleActive);
	}
}

void ASpike::SwitchActive(bool Active)
{
	puzzleActive = Active;
	activation = Active;
	playAnimation = true;
}