// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacter_AnimInstance.generated.h"

UCLASS()
class WA_API UPlayerCharacter_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerCharacter_AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	bool IsDash;

public:
	void SetDash(bool IsDashing);
};
