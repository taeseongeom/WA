// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckRoomClear.h"

// Add default functionality here for any ICheckRoomClear functions that are not pure virtual.

bool ICheckRoomClear::GetClear()
{
	return isClear;
}

void ICheckRoomClear::SetClearCheckObject(bool value)
{
	isClearCheckObject = value;
}
