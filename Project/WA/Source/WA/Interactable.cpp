// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"


void IInteractable::SetInteractability(bool is_interactable)
{
	isInteractable = is_interactable;
}
bool IInteractable::IsInteractable() const
{
	return isInteractable;
}