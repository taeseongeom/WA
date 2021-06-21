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
	// Sets default values for this actor's properties
	ADefaultPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	//Reset Function
	virtual void BeginSetup(FVector pos, FRotator rot);
public:
	// Reset Function
	virtual void InitializePuzzle();
	virtual bool GetPuzzleActive();
	virtual void SetParentRoom(ARoomActor* value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere)
	ARoomActor* parentRoom;
	UPROPERTY(VisibleAnywhere)
	bool puzzleActive;
private: // Reset Property
	FVector initPos;
	FRotator initRot;
	UPROPERTY(EditAnywhere, Category = "Init")
	bool initpuzzleActive;
	UPROPERTY(EditAnywhere, Category = "Init")
	int32 roomNum;
	UPROPERTY(EditAnywhere, Category = "Init")
	bool isInitBreakableBox;
	UPROPERTY()
	TSubclassOf<class ABreakableBox> breakableBoxBlueprint;
	UPROPERTY()
	class ABreakableBox* breakableBox;
};