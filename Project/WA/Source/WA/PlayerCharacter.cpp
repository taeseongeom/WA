// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	Tags.Add(FName("Character"));

	state = ECharacterState::Idle;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	move_speed = 300.0f;
	jump_power = 500.0f;
	jumping = true;

	velocity = FVector::ZeroVector;
	interactObject = NULL;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = jump_power;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &APlayerCharacter::InputForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacter::InputLeftRight);
	PlayerInputComponent->BindAction(TEXT("MoveJump"), IE_Pressed, this, &APlayerCharacter::MoveJump);
	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &APlayerCharacter::BeginInteraction);
	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Released, this, &APlayerCharacter::EndInteraction);
}

void APlayerCharacter::InputForwardBackward(float value)
{
	switch (state)
	{
	case ECharacterState::Idle:
		MoveForwardBackward(value);
		break;
	case ECharacterState::Shooting:
		if (value > 0) RotateShooter(0);
		else if (value < 0) RotateShooter(1);
		break;
	}
}

void APlayerCharacter::InputLeftRight(float value)
{
	switch (state)
	{
	case ECharacterState::Idle:
		MoveLeftRight(value);
		break;
	case ECharacterState::Shooting:
		if (value > 0) RotateShooter(2);
		else if (value < 0) RotateShooter(3);
		break;
	}
}

void APlayerCharacter::MoveForwardBackward(float value)
{
	velocity.X = value;
	AddMovementInput(velocity.GetSafeNormal());
}
void APlayerCharacter::MoveLeftRight(float value)
{
	velocity.Y = value;
	AddMovementInput(velocity.GetSafeNormal());
}
void APlayerCharacter::RotateShooter(int dir)
{
	if (interactObject == NULL) return;

	switch (dir)
	{
	case 0:
		interactObject->SetActorRotation(FMath::Lerp(interactObject->GetActorRotation(),
			FRotator(0, 0, 0), 0.5f));
		break;
	case 1:
		interactObject->SetActorRotation(FMath::Lerp(interactObject->GetActorRotation(),
			FRotator(0, 180.0f, 0), 0.5f));
		break;
	case 2:
		interactObject->SetActorRotation(FMath::Lerp(interactObject->GetActorRotation(),
			FRotator(0, 90.0f, 0), 0.5f));
		break;
	case 3:
		interactObject->SetActorRotation(FMath::Lerp(interactObject->GetActorRotation(),
			FRotator(0, 270.0f, 0), 0.5f));
		break;
	}
}
void APlayerCharacter::MoveJump()
{
	Jump();
}

void APlayerCharacter::EndInteraction()
{
	EndInteractionWithPuzzle.Broadcast();
}

void APlayerCharacter::BeginInteraction()
{
	BeginInteractionWithPuzzle.Broadcast();
}

void APlayerCharacter::HoldMovableBox(int dir_code, FVector box_pos)
{
	FVector dist = GetActorLocation() - box_pos;
	switch (dir_code)
	{
	case 0:
		//SetActorLocation(GetActorLocation() + FVector(-10.0f, 0.0f, 0.0f));
		SetActorLocation(box_pos + FVector(-92.0f, dist.Y, dist.Z));
		break;

	case 1:
		//SetActorLocation(GetActorLocation() + FVector(10.0f, 0.0f, 0.0f));
		SetActorLocation(box_pos + FVector(92.0f, dist.Y, dist.Z));
		break;

	case 2:
		//SetActorLocation(GetActorLocation() + FVector(0.0f, -10.0f, 0.0f));
		SetActorLocation(box_pos + FVector(dist.X, -92.0f, dist.Z));
		break;

	case 3:
		//SetActorLocation(GetActorLocation() + FVector(0.0f, 10.0f, 0.0f));
		SetActorLocation(box_pos + FVector(dist.X, 92.0f, dist.Z));
		break;
	}
}

void APlayerCharacter::SetCharacterState(ECharacterState cs) {
	state = cs;
}

void APlayerCharacter::SetInteractObject(AActor * obj)
{
	if (interactObject == NULL)
		interactObject = obj;
}

void APlayerCharacter::ClearInteractObject()
{
	interactObject = NULL;
}
