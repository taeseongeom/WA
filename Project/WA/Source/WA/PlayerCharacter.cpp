// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	Tags.Add(FName("Character"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	move_speed = 300.0f;
	jump_power = 500.0f;
	jumping = true;

	velocity = FVector::ZeroVector;
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

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &APlayerCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacter::MoveLeftRight);
	PlayerInputComponent->BindAction(TEXT("MoveJump"), IE_Pressed, this, &APlayerCharacter::MoveJump);

	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &APlayerCharacter::Interaction);
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
void APlayerCharacter::MoveJump()
{
	Jump();
}

void APlayerCharacter::Interaction()
{
	InteractionWithPuzzle.Broadcast();
}