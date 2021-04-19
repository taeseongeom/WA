// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Switchlever.generated.h"

UCLASS()
class WA_API ASwitchlever : public ADefaultPuzzle, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchlever();
private:
	UPROPERTY(EditAnywhere)
	ADefaultPuzzle* TurnOnTarget;

	UPROPERTY()
	class APlayerCharacter* pc;

	UPROPERTY(EditAnywhere, Category = "Init")
	bool initIsTurnOn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
public:	
	// Called every frame
	virtual void Interact() override;
	virtual void InitializePuzzle() override;
};
