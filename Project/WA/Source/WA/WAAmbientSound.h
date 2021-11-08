// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "WAAmbientSound.generated.h"

/**
 * 
 */
UCLASS()
class WA_API AWAAmbientSound : public AAmbientSound
{
	GENERATED_BODY()


private:
	int stage;
	int currentPlayIndex;
	UPROPERTY(EditAnywhere, Category = "BGM")
	TArray<class USoundBase*> bgms;
public:
	virtual void BeginPlay() override;
	void SwapRoomBGM(int roomNum);
	void MuteBGM();
	void SetStage(int value);
};
