// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Switchable.generated.h"

UINTERFACE(MinimalAPI)
class USwitchable : public UInterface
{
	GENERATED_BODY()
};

class WA_API ISwitchable
{
	GENERATED_BODY()

protected:
	bool isTurnOn;
public:
	virtual void OnSwitch() = 0;
	bool GetIsTurnOn() const;
	void SetIsTurnOn(bool value);
};
