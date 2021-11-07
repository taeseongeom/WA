// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "MessageVolume.generated.h"

UCLASS()
class WA_API AMessageVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AMessageVolume();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	bool isUsed;

	// Mesasge to display
	UPROPERTY(EditAnywhere, Category = "Message")
	FString message;
	// Duration to expose message. 0 is INFINITE. (sec)
	UPROPERTY(EditAnywhere, Category = "Message")
	float exposureTime;
};
