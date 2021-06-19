// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Stage2_Anim.h"


UBoss_Stage2_Anim::UBoss_Stage2_Anim()
{
	IsMoving = false;
	IsDamaged = false;
	IsDie = false;
	
	PatternNumber = 0;
}

void UBoss_Stage2_Anim::AnimNotify_DamageEnd()
{
	IsDamaged = false;
	PatternNumber = 0;
}
void UBoss_Stage2_Anim::AnimNotify_AttackEnd()
{
	PatternNumber = 0;
}

void UBoss_Stage2_Anim::StartMoving()
{
	IsMoving = true;
}
void UBoss_Stage2_Anim::StopMoving()
{
	IsMoving = false;
}
void UBoss_Stage2_Anim::GetHit()
{
	IsDamaged = true;
}
void UBoss_Stage2_Anim::Die()
{
	IsDie = true;
}
void UBoss_Stage2_Anim::Attack(int32 PatternCode)
{
	if (PatternCode >= 1 && PatternCode <= 4)
	{
		IsDamaged = false;
		PatternNumber = PatternCode;
	}
}