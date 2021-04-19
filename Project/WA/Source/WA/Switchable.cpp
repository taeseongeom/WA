// Fill out your copyright notice in the Description page of Project Settings.


#include "Switchable.h"

bool ISwitchable::GetIsTurnOn() const{
	return isTurnOn;
}

void ISwitchable::SetIsTurnOn(bool value){
	isTurnOn = value;
}