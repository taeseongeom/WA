// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DefaultPuzzle.h"
#include "MovableBox.generated.h"

UCLASS()
class WA_API AMovableBox : public ADefaultPuzzle, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AMovableBox();

private:
	UPROPERTY()
	UStaticMeshComponent* boxBody;

	UPROPERTY()
	class APlayerCharacter* pc;

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

	virtual void InitializePuzzle() override;
	virtual void Interact() override;
};
