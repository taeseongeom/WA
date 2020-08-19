// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "PuzzleObject.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	move_speed = 300.f;
	jump_power = 500.f;

	velocity = velocity.ZeroVector;

	simultaneousX = false;
	simultaneousY = false;

	jumping = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (velocity * DeltaTime));

	if (jumping)
	{
		velocity.Z -= 5.f;
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("MoveForward", IE_Pressed, this, &APlayerPawn::MoveForward);
	InputComponent->BindAction("MoveForward", IE_Released, this, &APlayerPawn::StopForward);

	InputComponent->BindAction("MoveBackward", IE_Pressed, this, &APlayerPawn::MoveBackward);
	InputComponent->BindAction("MoveBackward", IE_Released, this, &APlayerPawn::StopBackward);

	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerPawn::MoveLeft);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &APlayerPawn::StopLeft);

	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerPawn::MoveRight);
	InputComponent->BindAction("MoveRight", IE_Released, this, &APlayerPawn::StopRight);

	InputComponent->BindAction("MoveJump", IE_Pressed, this, &APlayerPawn::MoveJump);

	InputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerPawn::Interaction);
}


void APlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(staticObjectTag))
	{
		if (OtherActor->GetActorLocation().Z < GetActorLocation().Z)
		{
			jumping = false;
		}

		SetActorLocation(GetActorLocation() + FVector(0, 0, 0));

		velocity.Z = 0;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Start Overlap"));
	}
}

void APlayerPawn::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(staticObjectTag))
	{
		jumping = true;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("End Overlap"));
	}
}


void APlayerPawn::MoveForward()
{
	if (velocity.X != 0.f)
	{
		simultaneousX = true;
	}
	velocity.X = move_speed;
}
void APlayerPawn::StopForward()
{
	if (simultaneousX)
	{
		velocity.X = move_speed * -1;
	}
	else
	{
		velocity.X = 0.f;
	}
	simultaneousX = false;
}

void APlayerPawn::MoveBackward()
{
	if (velocity.X != 0.f)
	{
		simultaneousX = true;
	}
	velocity.X = move_speed * -1;
}
void APlayerPawn::StopBackward()
{
	if (simultaneousX)
	{
		velocity.X = move_speed;
	}
	else
	{
		velocity.X = 0.f;
	}
	simultaneousX = false;
}

void APlayerPawn::MoveLeft()
{
	if (velocity.Y != 0.f)
	{
		simultaneousY = true;
	}
	velocity.Y = move_speed * -1;
}
void APlayerPawn::StopLeft()
{
	if (simultaneousY)
	{
		velocity.Y = move_speed;
	}
	else
	{
		velocity.Y = 0.f;
	}
	simultaneousY = false;
}

void APlayerPawn::MoveRight()
{
	if (velocity.Y != 0.f)
	{
		simultaneousY = true;
	}
	velocity.Y = move_speed;
}
void APlayerPawn::StopRight()
{
	if (simultaneousY)
	{
		velocity.Y = move_speed * -1;
	}
	else
	{
		velocity.Y = 0.f;
	}
	simultaneousY = false;
}

void APlayerPawn::MoveJump()
{
	velocity.Z = jump_power;
}

void APlayerPawn::Interaction()
{
	/*void (APuzzleObject::*puzzleInteract)(void) = APuzzleObject::Interaction;

	puzzleInteract;*/
}