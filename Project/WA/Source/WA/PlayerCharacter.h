// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class APlayerCamera;
class UInGameUI;
class UPlayerCharacter_AnimInstance;

DECLARE_MULTICAST_DELEGATE(FInteractDelegate);

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	BoxMoving UMETA(DisplayName = "Moving MovableBox"),
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

	// 이동 속도
	FVector velocity;

	UPROPERTY(VisibleAnywhere, Category = "State")
	ECharacterState state;

	// 카메라 생성 여부. 첫 착지 이후에 생성됩니다.
	bool camera_init;
	UPROPERTY()
	APlayerCamera* playerCamera;
	// 카메라 시점에 따른 캐릭터의 방향
	FVector viewportDirection;

	UPROPERTY()
	UInGameUI* inGameUI;

	UPROPERTY()
	class AWAGameModeBase* WaGMB;

	UPROPERTY()
	UPlayerCharacter_AnimInstance* animInstance;

	// 현재 연결된 MovableBox
	class AMovableBox* holdingBox;

	// 착지 여부. 착지 후에 대시 쿨타임을 진행합니다.
	bool has_landed;
	// 현재 대시 가능 횟수
	int cur_dashCount;
	// 현재 대시 지속시간
	float cur_dashTime;
	// 현재 대시 재사용 대기시간
	float cur_dashCooltime;

	// 현재 무적 시간(피격되지 않으며, 이동도 불가)
	float cur_invincibleTime;

	bool blockDir_forward;
	bool blockDir_backward;
	bool blockDir_right;
	bool blockDir_left;

	int8 interactionRegionOverlap;


	void InputForwardBackward(float value);
	void InputLeftRight(float value);
	void MoveJump();
	void MoveDashBegin();
	void MoveDashEnd();
	void Interaction();

	void Death();

public:
	FInteractDelegate InteractionWithPuzzle;

	void SetCharacterState(ECharacterState cs);

	void IncreaseDashCount(int increase_num);
	void DecreaseDashCount(int decrease_num);

	APlayerCamera* GetPlayerCamera() const;
	void SetViewportDirection(const FVector& Dir);

	// 플레이어의 이동을 제한합니다. 각 매개변수가 true면 해당 이동을 막습니다.
	void SetBlockPlayerMoveDirection(bool Forward, bool Backward, bool Right, bool Left);

	void SetHealthPoint(float value);
	float GetHealthPoint() const;
	void InitInGameUI();
	void ActivateInGameUI();
	void DeactivateInGameUI();
	void StartCutScene();

	void DisplayInteractionUI(bool IsShown);

	// 해당 캐릭터와 Movable Box를 연결합니다. nullptr인 경우 연결을 해제합니다.
	void ConnectWithCharacter(AMovableBox* HoldingMovableBox);
};
