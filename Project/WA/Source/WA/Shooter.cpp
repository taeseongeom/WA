// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "PlayerCharacter.h"
#include "Shooter_Bullet.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


AShooter::AShooter()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetInteractability(false);

	puzzleActive = false;
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		pc = *iter;
		iter->InteractionWithPuzzle.AddUFunction(this, FName("Interact"));
		break;
	}
	pController = GetWorld()->GetFirstPlayerController();
}

void AShooter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(true);
	}
}

void AShooter::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		SetInteractability(false);
	}
}

void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (puzzleActive)
	{
		if (pController->WasInputKeyJustReleased(EKeys::X))
			ShootBullet();
		else
			RotateShooter();
	}
}

void AShooter::InitializePuzzle(int room_number)
{
	if (roomNum == room_number)
	{

	}
}

void AShooter::Interact()
{
	if (IsInteractable()) // Interact Begin
	{
		puzzleActive = !puzzleActive;
		pc->SetCharacterState(ECharacterState::Shooting);
	}
}

void AShooter::ShootBullet()
{
	puzzleActive = !puzzleActive;
	pc->SetCharacterState(ECharacterState::Idle);
	AShooter_Bullet* bullet = (AShooter_Bullet*)GetWorld()->SpawnActor<AActor>(BulletBlueprint, GetActorLocation(), GetActorRotation());
	bullet->SetStack(BulletSpeed, Crash_count);
}

void AShooter::RotateShooter()
{
	float hor = pc->InputComponent->GetAxisValue("MoveForwardBackward");
	float ver = pc->InputComponent->GetAxisValue("MoveLeftRight");
	if (hor != 0 && ver != 0)
	{
		direction.X = hor;
		direction.Y = ver;
	}
	else if (hor != 0 && ver == 0)
	{
		direction.X = hor;
		direction.Y = 0;
	}
	else if (ver != 0 && hor == 0)
	{
		direction.X = 0;
		direction.Y = ver;
	}
	direction.Normalize();
	SetActorRotation(FRotator(0, FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X)), 0));
	pc->SetActorRotation(GetActorRotation());
	pc->SetActorLocation(GetActorLocation() + -GetActorForwardVector() * 40);
}