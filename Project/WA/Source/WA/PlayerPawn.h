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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


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
	
	FVector velocity;

	bool simultaneousX;
	bool simultaneousY;

	int num_overlappingObj;


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
