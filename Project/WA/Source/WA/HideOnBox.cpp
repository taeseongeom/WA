// Fill out your copyright notice in the Description page of Project Settings.


#include "HideOnBox.h"

// Add default functionality here for any IHideOnBox functions that are not pure virtual.

bool IHideOnBox::IsHiding() { return isHiding; }

void IHideOnBox::SetHide(bool value) { isHiding = value; }
