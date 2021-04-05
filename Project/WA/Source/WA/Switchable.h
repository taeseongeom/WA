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

public:
	virtual void OnSwitch() = 0;
};
