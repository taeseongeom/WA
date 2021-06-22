// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TitleSoundEffect.generated.h"

UCLASS()
class WA_API ATitleSoundEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATitleSoundEffect();

	void PlayBtnEffect(USoundBase* source);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UAudioComponent* audioComp;
};
