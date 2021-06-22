// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Switchable.h"
#include "DefaultPuzzle.h"
#include "DirectionChanger.generated.h"

UCLASS()
class WA_API ADirectionChanger : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	ADirectionChanger();

private:
	UPROPERTY(EditAnywhere, Category = "Time")
	float revealTime;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	bool isCounterclockwise;

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor activeColor;
	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor deactiveColor;

	UPROPERTY()
	class UArrowComponent* arrowMesh;

	float currentTick;

	bool changeActive;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InitializePuzzle() override;
	virtual void OnSwitch() override;
};
