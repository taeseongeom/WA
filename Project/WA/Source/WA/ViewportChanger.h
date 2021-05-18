// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewportChanger.generated.h"

UCLASS()
class WA_API AViewportChanger : public AActor
{
	GENERATED_BODY()
	
public:	
	AViewportChanger();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	// Relative location of the camera when character enter this region.
	UPROPERTY(EditAnywhere, Category = "Camera Transform")
	FVector cameraPos;
	// Relative rotation of the camera when character enter this region.
	UPROPERTY(EditAnywhere, Category = "Camera Transform")
	FRotator cameraRot;
};
