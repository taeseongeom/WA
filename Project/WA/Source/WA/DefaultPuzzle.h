// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HideOnBox.h"
#include "DefaultPuzzle.generated.h"

class ARoomActor;

UCLASS()
class WA_API ADefaultPuzzle : public AActor, public IHideOnBox
{
	GENERATED_BODY()
	
public:	
	ADefaultPuzzle();

protected:
	virtual void BeginPlay() override;
protected:
	// Reset Function
	virtual void BeginSetup(FVector pos, FRotator rot);
public:
	// Reset Function
	virtual void InitializePuzzle();
	virtual bool GetPuzzleActive();
	virtual void SetParentRoom(ARoomActor* value);
public:	
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere)
	ARoomActor* parentRoom;
	UPROPERTY(VisibleAnywhere)
	bool puzzleActive;
	UPROPERTY()
	class UAudioComponent* audioComp;
	UPROPERTY(EditAnywhere, Category = "Sound")
	TArray<class USoundBase*> effects;
private: // Reset Properties
	FVector initPos;
	FRotator initRot;
	UPROPERTY(EditAnywhere, Category = "Init")
	bool initpuzzleActive;
	UPROPERTY(EditAnywhere, Category = "Init")
	int32 roomNum;
};