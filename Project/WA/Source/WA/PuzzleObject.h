// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzleObject.generated.h"

UCLASS()
class WA_API APuzzleObject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APuzzleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// The size of box region that recognize overlapping to interact.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FVector boxExtent;


	// Be excuted by pressing interaction key.
	void Interaction();
};
