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
	FVector velocity;

	int num_overlappingObj;


	// Be excuted by pressing interaction key.
	UFUNCTION()
	virtual void Interaction() override;
};
