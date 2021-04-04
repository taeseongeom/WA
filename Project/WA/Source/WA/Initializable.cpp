// Fill out your copyright notice in the Description page of Project Settings.


#include "Initializable.h"


void IInitializable::BeginSetup(FVector pos, FRotator rot)
{
	initPos = pos;
	initRot = rot;
}