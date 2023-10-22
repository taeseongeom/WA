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
	AShooter_Bullet();

private:
	float Speed;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosion;
	UPROPERTY(VisibleAnywhere)
	int Crash_count;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	void SetStack(float Speed, int Crash_count);

	// Get, Set
	int GetCrashCount() { return Crash_count; }
	void SetCrashCount(int value) { Crash_count = value; }
	float GetSpeed() { return Speed; }
	void SetSpeed(float value) { Speed = value; }
};
