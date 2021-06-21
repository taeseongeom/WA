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

	// ������ Ȱ��ȭ ����
	bool active;

public:
	void SwitchActive(bool IsActive);
};