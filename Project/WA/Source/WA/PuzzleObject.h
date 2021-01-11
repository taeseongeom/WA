// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleObject.generated.h"

UCLASS()
class WA_API APuzzleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleObject();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

	// Whether interaction region gizmo is shown or not on game. It is false by default.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Region")
	bool isShow;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool jumping;

private:
	FVector boxExtent;
	
	FVector velocity;

	int num_overlappingObj;
	bool isInteractable;


	// Be excuted by pressing interaction key.
	UFUNCTION()
	void Interaction();
};
