// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class WA_API IInteractable
{
	GENERATED_BODY()

private:
	bool isInteractable;

protected:
	bool puzzleActive;

	void SetInteractability(bool is_interactable);
	bool IsInteractable();

public:
	UFUNCTION()
	virtual void Interact() = 0;
};
