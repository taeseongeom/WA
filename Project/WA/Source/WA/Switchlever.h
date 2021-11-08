// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SwitchPuzzle.h"
#include "Switchlever.generated.h"

UCLASS()
class WA_API ASwitchlever : public ASwitchPuzzle, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASwitchlever();

private:
	UPROPERTY()
	class APlayerCharacter* pc;

	UPROPERTY()
	USceneComponent* leverMesh;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Interact() override;
};
