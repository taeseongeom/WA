// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableBox.h"

#include "PlayerCharacter.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AMovableBox::AMovableBox()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetInteractability(false);

	isInAirOnStart = false;
	gravitySpeed = 9.81f;
	inAir = false;
	fallSpeed = 0;

	distance = FVector::ZeroVector;

	pc = nullptr;
}

void AMovableBox::BeginPlay()
{
	Super::BeginPlay();

	SetTickGroup(TG_PostUpdateWork);

	inAir = isInAirOnStart;

	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
}

void AMovableBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(true);
		Cast<APlayerCharacter>(OtherActor)->DisplayInteractionUI(true);
	}
	else
	{
		bool res = false;
		FHitResult hit;

		if (puzzleActive)
		{
			if (FMath::Abs(distance.X) > FMath::Abs(distance.Y))
			{
				// Ban forward
				if (distance.X > 0)
				{
					res = GetWorld()->SweepSingleByChannel(
						hit,
						GetActorLocation(),
						GetActorLocation() + FVector(50, 0, 0) * GetActorScale().X + FVector(1, 0, 0),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel5,
						FCollisionShape::MakeBox(FVector(1, 48 * GetActorScale().Y, 48 * GetActorScale().Z)));

					pc->SetBlockPlayerMoveDirection(res, false, true, true);
				}
				// Ban backward
				else
				{
					res = GetWorld()->SweepSingleByChannel(
						hit,
						GetActorLocation(),
						GetActorLocation() + FVector(-50, 0, 0) * GetActorScale().X + FVector(-1, 0, 0),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel5,
						FCollisionShape::MakeBox(FVector(1, 48 * GetActorScale().Y, 48 * GetActorScale().Z)));

					pc->SetBlockPlayerMoveDirection(false, res, true, true);
				}
			}
			else
			{
				// Ban right
				if (distance.Y > 0)
				{
					res = GetWorld()->SweepSingleByChannel(
						hit,
						GetActorLocation(),
						GetActorLocation() + FVector(0, 50, 0) * GetActorScale().Y + FVector(0, 1, 0),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel5,
						FCollisionShape::MakeBox(FVector(48 * GetActorScale().X, 1, 48 * GetActorScale().Z)));

					pc->SetBlockPlayerMoveDirection(true, true, res, false);
				}
				// Ban left
				else
				{
					res = GetWorld()->SweepSingleByChannel(
						hit,
						GetActorLocation(),
						GetActorLocation() + FVector(0, -50, 0) * GetActorScale().Y + FVector(0, -1, 0),
						FQuat::Identity,
						ECollisionChannel::ECC_GameTraceChannel5,
						FCollisionShape::MakeBox(FVector(48 * GetActorScale().X, 1, 48 * GetActorScale().Z)));

					pc->SetBlockPlayerMoveDirection(true, true, false, res);
				}
			}
		}
		else
		{
			// Check landing
			res = GetWorld()->SweepSingleByChannel(
				hit,
				GetActorLocation(),
				GetActorLocation() + FVector(0, 0, -50) * GetActorScale().Z + FVector(0, 0, -1),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel5,
				FCollisionShape::MakeBox(FVector(48 * GetActorScale().X, 48 * GetActorScale().Y, 1)));
			
			inAir = !res;
			fallSpeed = 0;
		}
	}
}
void AMovableBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
		Cast<APlayerCharacter>(OtherActor)->DisplayInteractionUI(false);

		puzzleActive = false;
	}
	else
	{
		if (puzzleActive)
		{
			if (FMath::Abs(distance.X) > FMath::Abs(distance.Y))
				pc->SetBlockPlayerMoveDirection(false, false, true, true);
			else
				pc->SetBlockPlayerMoveDirection(true, true, false, false);
		}
		else
		{
			// Check landing
			FHitResult hit;
			bool res = GetWorld()->SweepSingleByChannel(
				hit,
				GetActorLocation(),
				GetActorLocation() + FVector(0, 0, -50) * GetActorScale().Z + FVector(0, 0, -1),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel5,
				FCollisionShape::MakeBox(FVector(48 * GetActorScale().X, 48 * GetActorScale().Y, 1)));
			
			inAir = !res;
			fallSpeed = 0;
		}
	}
}

void AMovableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (inAir && !IsHidden())
	{
		fallSpeed += gravitySpeed * DeltaTime;
		SetActorLocation(GetActorLocation() - FVector(0, 0, fallSpeed));
	}

	if (puzzleActive)
	{
		SetActorLocation(pc->GetActorLocation() + distance);
	}
}

void AMovableBox::InitializePuzzle()
{
	Super::InitializePuzzle();

	SetInteractability(false);
	
	inAir = isInAirOnStart;
	fallSpeed = 0;

	distance = FVector::ZeroVector;
}

void AMovableBox::Interact()
{
	if (IsInteractable())
	{
		puzzleActive = !puzzleActive;

		// 캐릭터와 연결
		if (puzzleActive)
		{
			// 유효한 범위 내에 있을 경우
			FVector temp_dist = pc->GetActorLocation() - GetActorLocation();
			if ((-50.0f < temp_dist.Y && temp_dist.Y < 50.0f) ||
				(-50.0f < temp_dist.X && temp_dist.X < 50.0f))
			{
				float gap = 34.0f + 50.0f * GetActorScale().X + 20.0f * GetActorScale().X;
				FVector player_pos = pc->GetActorLocation();
				
				// Forward available
				if (temp_dist.X < -50.0f)
				{
					pc->SetActorLocation(FVector(GetActorLocation().X - gap, player_pos.Y, player_pos.Z));
					pc->SetBlockPlayerMoveDirection(false, false, true, true);
				}
				// Backward available
				else if (temp_dist.X > 50.0f)
				{
					pc->SetActorLocation(FVector(GetActorLocation().X + gap, player_pos.Y, player_pos.Z));
					pc->SetBlockPlayerMoveDirection(false, false, true, true);
				}
				// Right available
				else if (temp_dist.Y < -50.0f)
				{
					pc->SetActorLocation(FVector(player_pos.X, GetActorLocation().Y - gap, player_pos.Z));
					pc->SetBlockPlayerMoveDirection(true, true, false, false);
				}
				// Left available
				else if (temp_dist.Y > 50.0f)
				{
					pc->SetActorLocation(FVector(player_pos.X, GetActorLocation().Y + gap, player_pos.Z));
					pc->SetBlockPlayerMoveDirection(true, true, false, false);
				}

				pc->ConnectWithCharacter(this);
				distance = GetActorLocation() - pc->GetActorLocation();
			}
			else
			{
				puzzleActive = false;
			}
		}
		// 캐릭터와 연결 해제
		else
		{
			// Disconnect with character
			pc->SetBlockPlayerMoveDirection(false, false, false, false);
			pc->ConnectWithCharacter(nullptr);
			distance = FVector::ZeroVector;

			// Check landing
			FHitResult hit;
			bool res = GetWorld()->SweepSingleByChannel(
				hit,
				GetActorLocation(),
				GetActorLocation() + FVector(0, 0, -50) * GetActorScale().Z + FVector(0, 0, -1),
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel5,
				FCollisionShape::MakeBox(FVector(48 * GetActorScale().X, 48 * GetActorScale().Y, 1)));

			inAir = !res;
			fallSpeed = 0;
		}
	}
}

void AMovableBox::ForceDisconnect()
{
	puzzleActive = false;
	distance = FVector::ZeroVector;
}