// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleObject.generated.h"

UINTERFACE(MinimalAPI)
class UPuzzleObject : public UInterface
{
	GENERATED_BODY()
};

class WA_API IPuzzleObject
{
	GENERATED_BODY()

	
private:
	bool isInteractable;

protected:
	FVector boxExtent;


	void SetInteractability(bool is_interactable);
	bool IsInteractable();

public:
	UFUNCTION()
	virtual void Interact() = 0;
};
