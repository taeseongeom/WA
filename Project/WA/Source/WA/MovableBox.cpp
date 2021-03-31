// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableBox.h"
#include "PlayerCharacter.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AMovableBox::AMovableBox()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetInteractability(false);

	puzzleActive = false;

	gravitySpeed = 0.1f;
	overlapedObjectNum = 0;
	velocity = FVector::ZeroVector;
	distance = FVector::ZeroVector;
}

void AMovableBox::BeginPlay()
{
	Super::BeginPlay();

	SetTickGroup(TG_PostUpdateWork);

	boxBody = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (boxBody != nullptr)
	{
		boxBody->SetSimulatePhysics(true);
	}
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
	}
	else
	{
		boxBody->SetSimulatePhysics(false);
	}
}
void AMovableBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
		puzzleActive = false;
		OutOfInteractionRange();
	}
	else
	{
		boxBody->SetSimulatePhysics(true);
	}
}

void AMovableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (puzzleActive)
	{
		SetActorLocation(pc->GetActorLocation() + distance);
	}
}

void AMovableBox::Interact()
{
	if (IsInteractable())
	{
		puzzleActive = !puzzleActive;

		if (puzzleActive)
		{
			//boxBody->SetCollisionObjectType(ECC_GameTraceChannel3);		// object type을 moving_box로 변경

			SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 10.0f));
			FVector temp_dist = GetActorLocation() - pc->GetActorLocation();
			if ((temp_dist.X > -50.0f && temp_dist.X < 50.0f) ||
				(temp_dist.Y > -50.0f && temp_dist.Y < 50.0f))
			{
				if (temp_dist.X > 50.0f)
				{
					// forward
					pc->HoldMovableBox(0, GetActorLocation());
				}
				else if (temp_dist.X < -50.0f)
				{
					// backward
					pc->HoldMovableBox(1, GetActorLocation());
				}
				else if (temp_dist.Y > 50.0f)
				{
					// right
					pc->HoldMovableBox(2, GetActorLocation());
				}
				else if (temp_dist.Y < -50.0f)
				{
					// left
					pc->HoldMovableBox(3, GetActorLocation());
				}
			}

			distance = GetActorLocation() - pc->GetActorLocation();

			boxBody->SetSimulatePhysics(false);
			
			UE_LOG(LogTemp, Warning, TEXT("Interact"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Interact End"));
			distance = FVector::ZeroVector;
			OutOfInteractionRange();

			boxBody->SetSimulatePhysics(true);
		}
	}
}

void AMovableBox::OutOfInteractionRange()
{
	//boxBody->SetCollisionObjectType(ECC_WorldDynamic);
}