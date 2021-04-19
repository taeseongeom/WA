// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "WAGameModeBase.h"


APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	Tags.Add(FName("Character"));

	state = ECharacterState::Idle;

	health_point = 100.0f;
	invincible_time = 1.0f;
	move_speed = 600.0f;
	move_accel = 6000.0f;
	jump_power = 500.0f;
	dash_multiplier = 4.0f;
	dash_time = 0.4f;
	dash_cooldown = 3.0f;

	dash_count = 0;
	has_landed = false;
	cur_dashCount = dash_count;
	cur_dashTime = 0.0f;
	cur_dashCooltime = 0.0f;

	jumping = true;

	velocity = FVector::ZeroVector;

	// 캐릭터 이동 관련 초기값을 CharacterMovementComponent에 반영
	GetCharacterMovement()->MaxWalkSpeed = move_speed;
	GetCharacterMovement()->MaxAcceleration = move_accel;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 900.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = jump_power;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->FallingLateralFriction = GetCharacterMovement()->GroundFriction;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = move_speed;
	GetCharacterMovement()->MaxAcceleration = move_accel;
	GetCharacterMovement()->JumpZVelocity = jump_power;
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (cur_dashCount < dash_count)
	{
		has_landed = true;
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dash 실행
	if (ECharacterState::Dash == state)
	{
		AddMovementInput(GetActorForwardVector(), dash_multiplier);

		cur_dashTime += DeltaTime;
		if (cur_dashTime >= dash_time)	// Dash 종료
		{
			cur_dashCount--;
			cur_dashTime = 0.0f;
			cur_dashCooltime = 0.0f;

			// 최대 이동 속도 원상 복귀
			GetCharacterMovement()->MaxWalkSpeed = move_speed;
			GetCharacterMovement()->MaxAcceleration = move_accel;
			// 중력 다시 활성화
			GetCharacterMovement()->GravityScale = 1.0f;

			state = ECharacterState::Idle;
		}
	}
	// Dash 쿨다운 진행
	if (cur_dashCount < dash_count)
	{
		cur_dashCooltime += DeltaTime;
		if (cur_dashCooltime >= dash_cooldown)
		{
			if (!GetCharacterMovement()->IsFalling() || has_landed)
			{
				cur_dashCount++;
				cur_dashCooltime = cur_dashCooltime - dash_cooldown;
				if (cur_dashCount >= dash_count)
				{
					cur_dashCooltime = 0.0f;
				}
				has_landed = false;
			}
		}
	}
	if (GetActorLocation().Z < -300)
	{
		((AWAGameModeBase*)(GetWorld()->GetAuthGameMode()))->RoomReset();
		SetActorLocation(FVector(50.0f, 30.0f, 325.0f));
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &APlayerCharacter::InputForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacter::InputLeftRight);
	PlayerInputComponent->BindAction(TEXT("MoveJump"), IE_Pressed, this, &APlayerCharacter::MoveJump);
	PlayerInputComponent->BindAction(TEXT("MoveDash"), IE_Pressed, this, &APlayerCharacter::MoveDashBegin);
	PlayerInputComponent->BindAction(TEXT("MoveDash"), IE_Released, this, &APlayerCharacter::MoveDashEnd);
	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &APlayerCharacter::Interaction);
}

void APlayerCharacter::InputForwardBackward(float value)
{
	switch (state)
	{
	case ECharacterState::Idle:
		velocity.X = value;
		AddMovementInput(velocity.GetSafeNormal());
		break;
	case ECharacterState::Shooting:
		break;
	}
}
void APlayerCharacter::InputLeftRight(float value)
{
	switch (state)
	{
	case ECharacterState::Idle:
		velocity.Y = value;
		AddMovementInput(velocity.GetSafeNormal());
		break;
	case ECharacterState::Shooting:
		break;
	}
}
void APlayerCharacter::MoveJump()
{
	Jump();
}
void APlayerCharacter::MoveDashBegin()
{
	if (cur_dashCount > 0 && ECharacterState::Dash != state)
	{
		cur_dashTime = 0.0f;

		// 최대 이동 속도를 임시로 늘림
		GetCharacterMovement()->MaxWalkSpeed = move_speed * dash_multiplier;
		GetCharacterMovement()->MaxAcceleration = move_accel * dash_multiplier;
		// 임시로 중력 제거
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->Velocity.Z = 0.0f;

		state = ECharacterState::Dash;
	}
}
void APlayerCharacter::MoveDashEnd()
{
	if (ECharacterState::Dash == state)
	{
		cur_dashCount--;
		cur_dashTime = 0.0f;
		cur_dashCooltime = 0.0f;

		// 최대 이동 속도 원상 복귀
		GetCharacterMovement()->MaxWalkSpeed = move_speed;
		GetCharacterMovement()->MaxAcceleration = move_accel;
		// 중력 다시 활성화
		GetCharacterMovement()->GravityScale = 1.0f;

		state = ECharacterState::Idle;
	}
}
void APlayerCharacter::Interaction()
{
	InteractionWithPuzzle.Broadcast();
}

void APlayerCharacter::HoldMovableBox(int dir_code, FVector box_pos)
{
	FVector dist = GetActorLocation() - box_pos;
	switch (dir_code)
	{
	case 0:
		//SetActorLocation(GetActorLocation() + FVector(-10.0f, 0.0f, 0.0f));
		SetActorLocation(box_pos + FVector(-92.0f, dist.Y, dist.Z));
		break;

	case 1:
		//SetActorLocation(GetActorLocation() + FVector(10.0f, 0.0f, 0.0f));
		SetActorLocation(box_pos + FVector(92.0f, dist.Y, dist.Z));
		break;

	case 2:
		//SetActorLocation(GetActorLocation() + FVector(0.0f, -10.0f, 0.0f));
		SetActorLocation(box_pos + FVector(dist.X, -92.0f, dist.Z));
		break;

	case 3:
		//SetActorLocation(GetActorLocation() + FVector(0.0f, 10.0f, 0.0f));
		SetActorLocation(box_pos + FVector(dist.X, 92.0f, dist.Z));
		break;
	}
}

void APlayerCharacter::SetCharacterState(ECharacterState cs) {
	state = cs;
}

void APlayerCharacter::IncreaseDashCount(int increase_num)
{
	dash_count += increase_num;
	cur_dashCount = dash_count;
}
void APlayerCharacter::DecreaseDashCount(int decrease_num)
{
	dash_count -= decrease_num;
	if (cur_dashCount > dash_count)
	{
		cur_dashCount = dash_count;
		cur_dashCooltime = 0.0f;
	}
}