// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.h"
#include "MovableBox.generated.h"

UCLASS()
class WA_API AMovableBox : public AActor, public IPuzzleObject
{
	GENERATED_BODY()
	
public:	
	AMovableBox();

private:
	UPROPERTY()
	UStaticMeshComponent* boxBody;

	UPROPERTY()
	class APlayerCharacter* pc;

	bool puzzleActive;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float gravitySpeed;

	int overlapedObjectNum;

	FVector velocity;
	FVector distance;


	void OutOfInteractionRange();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
