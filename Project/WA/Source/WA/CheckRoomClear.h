// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CheckRoomClear.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCheckRoomClear : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WA_API ICheckRoomClear
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
private:
protected:
	bool isClear;
	bool isClearCheckObject;
public:
	UFUNCTION()
	virtual bool GetClear();
	UFUNCTION()
	virtual void SetClearCheckObject(bool value);
};
