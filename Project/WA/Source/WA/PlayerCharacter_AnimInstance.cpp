// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter_AnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"


UPlayerCharacter_AnimInstance::UPlayerCharacter_AnimInstance()
{
	CurrentSpeed = 0.0f;
	IsInAir = false;
	IsDash = false;

	stepEffect1 = nullptr;
	stepEffect2 = nullptr;
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
void UPlayerCharacter_AnimInstance::RegisterMoveSound(USoundBase* Step1, USoundBase* Step2)
{
	stepEffect1 = Step1;
	stepEffect2 = Step2;
}

void UPlayerCharacter_AnimInstance::AnimNotify_Step1()
{
	if (stepEffect1)
		UGameplayStatics::PlaySound2D(GetWorld(), stepEffect1);
}
void UPlayerCharacter_AnimInstance::AnimNotify_Step2()
{
	if (stepEffect2)
		UGameplayStatics::PlaySound2D(GetWorld(), stepEffect2);
}