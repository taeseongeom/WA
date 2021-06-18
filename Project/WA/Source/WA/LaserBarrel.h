// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBarrel.generated.h"

UCLASS()
class WA_API ALaserBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaserBarrel();

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Laser")
	int damage;
	UPROPERTY(EditAnywhere, Category = "Laser")
	float distance;

	// 레이저 활성화 여부
	bool active;

public:
	void SwitchActive(bool IsActive);
};
