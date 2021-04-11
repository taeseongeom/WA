// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FInteractDelegate);

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Shooting UMETA(DisplayName = "Shooting"),
};

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

private:
	// HP of character.
	UPROPERTY(EditAnywhere, Category = "Health")
	int health_point;
	// After damaged by enemy, character do not take damage during this time. Measure is a sec.
	UPROPERTY(EditAnywhere, Category = "Health")
	float invincible_time;

	// Speed of linear movement.
	UPROPERTY(EditAnywhere, Category = "Movement")
	float move_speed;
	// Acceleration speed of the movement.
	UPROPERTY(EditAnywhere, Category = "Movement")
	float move_accel;
	// Power of the jump. Affect to height of the jump.
	UPROPERTY(EditAnywhere, Category = "Movement")
	float jump_power;

	// Speed of dash.
	UPROPERTY(EditAnywhere, Category = "Dash")
	float dash_speed;
	// Dash maintain during this time. Measure is a sec.
	UPROPERTY(EditAnywhere, Category = "Dash")
	float dash_time;
	// Cool-time of the dash. Measure is a sec.
	UPROPERTY(EditAnywhere, Category = "Dash")
	float dash_cooldown;

	// Character movement velocity
	FVector velocity;

	UPROPERTY(VisibleAnywhere)
	ECharacterState state;

	void InputForwardBackward(float value);
	void InputLeftRight(float value);
	void MoveJump();

	void Interaction();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool jumping;

	// A tag of objects which do not affect by this object. Floors, walls, and other blocks that block the path or can be stepped on MUST contain this tag.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	FName staticObjectTag;

	FInteractDelegate InteractionWithPuzzle;

	void HoldMovableBox(int dir_code, FVector box_pos);
	void SetCharacterState(ECharacterState cs);
};
