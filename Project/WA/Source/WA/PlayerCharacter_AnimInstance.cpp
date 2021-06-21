// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter_AnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"


UPlayerCharacter_AnimInstance::UPlayerCharacter_AnimInstance()
{
	CurrentSpeed = 0.0f;
	IsInAir = false;
	IsDash = false;
}

void UPlayerCharacter_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	APawn* pawn = TryGetPawnOwner();
	if (IsValid(pawn))
	{
		CurrentSpeed = pawn->GetVelocity().SizeSquared();
		IsInAir = pawn->GetMovementComponent()->IsFalling();
	}
}

void UPlayerCharacter_AnimInstance::SetDash(bool IsDashing)
{
	IsDash = IsDashing;
}