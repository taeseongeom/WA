// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class WA_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float move_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float jump_power;
	
	FVector velocity;

	bool simultaneousX;
	bool simultaneousY;


	void MoveForward();
	void StopForward();

	void MoveBackward();
	void StopBackward();

	void MoveLeft();
	void StopLeft();

	void MoveRight();
	void StopRight();

	void MoveJump();

	void Interaction();
};
