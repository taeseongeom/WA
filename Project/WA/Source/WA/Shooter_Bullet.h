// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooter_Bullet.generated.h"

UCLASS()
class WA_API AShooter_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShooter_Bullet();

private:
	float Speed;
	UPROPERTY(VisibleAnywhere)
	int Crash_count;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStack(float Speed, int Crash_count);

	//Get, Set
	int GetCrashCount() { return Crash_count; }
	void SetCrashCount(int value) { Crash_count = value; }
	float GetSpeed() { return Speed; }
	void SetSpeed(float value) { Speed = value; }
};
