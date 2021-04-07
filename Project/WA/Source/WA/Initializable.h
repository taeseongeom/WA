// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Initializable.generated.h"

UINTERFACE(MinimalAPI)
class UInitializable : public UInterface
{
	GENERATED_BODY()
};

class WA_API IInitializable
{
	GENERATED_BODY()

private:
	FVector initPos;
	FRotator initRot;

protected:
	bool puzzleActive;

	int roomNum;

	/// <summary>
	/// Setup initial transform. This function MUST be called in BeginPlay function.
	/// </summary>
	/// <param name="pos">initial position</param>
	/// <param name="rot">initial rotator</param>
	void BeginSetup(FVector pos, FRotator rot);

	FVector GetInitPos() const;
	FRotator GetInitRot() const;

public:
	virtual void InitializePuzzle(int room_number) = 0;
};
