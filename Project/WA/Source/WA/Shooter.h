// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Initializable.h"
#include "Interactable.h"
#include "Shooter.generated.h"

UCLASS()
class WA_API AShooter : public AActor, public IInitializable, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AShooter();

private:
	UPROPERTY()
	class APlayerCharacter* pc;

	UPROPERTY()
	class APlayerController* pController;

	FVector direction;

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
	virtual void Tick(float DeltaTime) override;

	virtual void InitializePuzzle(int room_number) override;
	virtual void Interact() override;

private:
	void ShootBullet();
	void RotateShooter();
};
