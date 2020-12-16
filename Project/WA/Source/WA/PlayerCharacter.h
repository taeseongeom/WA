// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FInteractDelegate);

UCLASS()
class WA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Speed of linear movement.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float move_speed;
	// Power of the jump. Affect to height of the jump.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float jump_power;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool jumping;

	// A tag of objects which do not affect by this object. Floors, walls, and other blocks that block the path or can be stepped on MUST contain this tag.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	FName staticObjectTag;


	FInteractDelegate InteractionWithPuzzle;

private:
	FVector velocity;

	int num_overlappingObj;



	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);
	void MoveJump();

	void Interaction();
};
