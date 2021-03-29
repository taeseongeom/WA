// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.h"
#include "Shooter.generated.h"

UCLASS()
class WA_API AShooter : public AActor, public IPuzzleObject
{
	GENERATED_BODY()
	
public:	
	AShooter();

private:
	UPROPERTY()
	class APlayerCharacter* pc;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<class AActor> BulletBlueprint;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	float BulletSpeed;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	int Crash_count;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Interact() override;
	virtual void Interacted() override;
};
