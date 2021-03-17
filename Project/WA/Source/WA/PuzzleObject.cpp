// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleObject.h"


void IPuzzleObject::SetInteractability(bool is_interactable)
{
	isInteractable = is_interactable;
}
bool IPuzzleObject::IsInteractable()
{
	return isInteractable;
}