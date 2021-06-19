// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Boss_Stage2_Anim.generated.h"

UCLASS()
class WA_API UBoss_Stage2_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBoss_Stage2_Anim();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	bool IsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	bool IsDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	bool IsDie;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", Meta = (AllowPrivateAccess = true))
	int32 PatternNumber;

	UFUNCTION()
	void AnimNotify_DamageEnd();
	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	void StartMoving();
	void StopMoving();

	void GetHit();
	void Die();

	/// <summary>
	/// 공격 애니메이션을 재생합니다.
	/// </summary>
	/// <param name="PatternCode">공격 패턴의 번호 (1, 2, 3, 4)</param>
	void Attack(int32 PatternCode);
};
