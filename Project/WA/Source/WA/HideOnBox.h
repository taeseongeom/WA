// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HideOnBox.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHideOnBox : public UInterface
{
	GENERATED_BODY()
};

class WA_API IHideOnBox
{
	GENERATED_BODY()
private:
	bool isHiding;
protected:
	bool IsHiding();
public:
	void SetHide(bool value);
};
