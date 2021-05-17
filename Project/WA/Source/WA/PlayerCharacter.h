// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class APlayerCamera;

DECLARE_MULTICAST_DELEGATE(FInteractDelegate);

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Shooting UMETA(DisplayName = "Shooting"),
	Dash UMETA(DisplayName = "Dash"),
	KnockBack UMETA(DisplayName = "Knock-Back")
};

UCLASS()
class WA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	// Multiplier of the move_speed. dash_speed = move_speed * dash_multiplier.
	UPROPERTY(EditAnywhere, Category = "Movement|Dash")
	float dash_multiplier;
	// Dash maintain during this time. Measure is a sec.
	UPROPERTY(EditAnywhere, Category = "Movement|Dash")
	float dash_time;
	// Cool-time of the dash. Measure is a sec.
	UPROPERTY(EditAnywhere, Category = "Movement|Dash")
	float dash_cooldown;
	// The counts of dashes that a character can do. (UPROPERTY is for the test)
	UPROPERTY(EditAnywhere, Category = "Movement|Dash")
	int dash_count;

	UPROPERTY(EditAnywhere, Category = "Movement|Knock-Back")
	float knockBack_speed;
	UPROPERTY(EditAnywhere, Category = "Movement|Knock-Back")
	float knockBack_decrease;

	// 카메라 생성 여부. 첫 착지 시에 카메라가 생성됩니다.
	bool camera_init;
	
	// 캐릭터 이동 속도
	FVector velocity;

	UPROPERTY(VisibleAnywhere, Category = "State")
	// 캐릭터 상태
	ECharacterState state;

	UPROPERTY()
	APlayerCamera* playerCamera;

	// 캐릭터의 착지 여부. 대시 카운트 회복 여부를 판단할 때 사용됩니다.
	bool has_landed;
	// 현재 남은 대시 사용가능 횟수
	int cur_dashCount;
	// 현재 경과된 대시 지속 시간
	float cur_dashTime;
	// 현재 경과된 대시 쿨타임
	float cur_dashCooltime;

	// 현재 경과된 무적 시간(피격 지속 시간)
	float cur_invincibleTime;


	void InputForwardBackward(float value);
	void InputLeftRight(float value);
	void MoveJump();
	void MoveDashBegin();
	void MoveDashEnd();
	void Interaction();

	void Death();

public:
	FInteractDelegate InteractionWithPuzzle;

	void HoldMovableBox(int dir_code, FVector box_pos);
	void SetCharacterState(ECharacterState cs);

	void IncreaseDashCount(int increase_num);
	void DecreaseDashCount(int decrease_num);

	APlayerCamera* GetPlayerCamera() const;
};
