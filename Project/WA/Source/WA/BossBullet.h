// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "BossBullet.generated.h"

UCLASS()
class WA_API ABossBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossBullet();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	int damage;

	bool isMoving;

	FVector startPos;
	FVector targetPos;
	FVector targetDir;

	float curTime;
	float travelTime;
	float speed;

	UPROPERTY()
	UStaticMeshComponent* mesh;


	void InitializeData();

public:
	void MoveToLocation(const FVector& Destination, float TravelTime);
	void MoveToDirection(const FVector& Direction, float Speed, float LifeTime = 0);

	void ChangeColor(const FColor& Color);
};
