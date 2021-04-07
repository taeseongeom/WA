// Fill out your copyright notice in the Description page of Project Settings.


#include "Initializable.h"


void IInitializable::BeginSetup(FVector pos, FRotator rot)
{
	initPos = pos;
	initRot = rot;
}

FVector IInitializable::GetInitPos() const
{
	return initPos;
}
FRotator IInitializable::GetInitRot() const
{
	return initRot;
}