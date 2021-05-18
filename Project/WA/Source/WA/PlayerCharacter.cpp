// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerCamera.h"
#include "WAGameModeBase.h"


APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	Tags.Add(FName("Character"));

	velocity = FVector::ZeroVector;
	state = ECharacterState::Idle;
	playerCamera = nullptr;

	health_point = 100.0f;
	invincible_time = 1.0f;

	move_speed = 800.0f;
	move_accel = 6000.0f;
	jump_power = 500.0f;

	dash_multiplier = 4.0f;
	dash_time = 0.4f;
	dash_cooldown = 3.0f;
	dash_count = 0;

	knockBack_speed = 2.0f;
	knockBack_decrease = 0.01f;

	camera_init = false;

	has_landed = false;
	cur_dashCount = dash_count;
	cur_dashTime = 0.0f;
	cur_dashCooltime = 0.0f;

	cur_invincibleTime = 0.0f;

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

	AWAGameModeBase* WaGMB = (AWAGameModeBase*)(GetWorld()->GetAuthGameMode());
	if (WaGMB)
	{
		WaGMB->SetRespawnPoint(GetActorLocation());
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	// 첫 착지 시, 카메라 생성
	if (!camera_init)
	{
		camera_init = true;

		UCameraComponent* camera = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));

		playerCamera = GetWorld()->SpawnActor<APlayerCamera>(
			camera->GetComponentTransform().GetLocation(),
			camera->GetComponentTransform().GetRotation().Rotator());
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(playerCamera);
		playerCamera->SetInitialize(
			this, 
			camera->GetComponentTransform().GetLocation() - GetActorLocation(), 
			camera->GetComponentTransform().GetRotation().Rotator());

		camera->DestroyComponent();
	}
	
	// dash 횟수 충전
	if (cur_dashCount < dash_count)
	{
		has_landed = true;
	}
}

float APlayerCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (ECharacterState::KnockBack != state)
	{
		health_point -= Damage;

		// 넉백
		// 단순 뒤로 이동도 좋고, ForwardVector 기준으로 반대 방향에 목적지 잡아놓고 선형보간 연산으로 이동시키는 것도 좋다.
		// 지속시간은 invincible과 동일. 이동을 금지해야 하므로 state 변경이 필요하며, Tick에 내용 구현이 이루어져야 한다.
		state = ECharacterState::KnockBack;
		velocity = GetActorForwardVector() * -knockBack_speed;
	}

	// 사망
	if (health_point <= 0)
	{
		Death();
	}

	return health_point;
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

	// 넉백
	if (ECharacterState::KnockBack == state)
	{
		cur_invincibleTime += DeltaTime;
		if (cur_invincibleTime > invincible_time)
		{
			cur_invincibleTime = 0.0f;
			state = ECharacterState::Idle;
		}

		velocity *= (1.0f - knockBack_decrease);
		SetActorLocation(GetActorLocation() + velocity);
	}

	// 아래로 떨어지면 사망
	if (GetActorLocation().Z < -300)
	{
		Death();
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
		if (!isblockForwardBackwardMove)
		{
			velocity.X = value;
			AddMovementInput(velocity.GetSafeNormal());
		}
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
		if (!isblockLeftRightMove)
		{
			velocity.Y = value;
			AddMovementInput(velocity.GetSafeNormal());
		}
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

void APlayerCharacter::Death()
{
	// 초기화
	//UE_LOG(LogTemp, Warning, TEXT("Character has dead..."));
	AWAGameModeBase* WaGMB = (AWAGameModeBase*)(GetWorld()->GetAuthGameMode());
	WaGMB->RoomReset();
	SetActorLocation(WaGMB->GetRespawnPoint());

	health_point = 3;

	velocity = FVector::ZeroVector;

	state = ECharacterState::Idle;

	cur_invincibleTime = 0.0f;
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

APlayerCamera* APlayerCharacter::GetPlayerCamera() const
{
	return playerCamera;
}

void APlayerCharacter::SetBlockPlayerMoveDirection(bool isHorizon, bool value)
{
	if (isHorizon)
		isblockLeftRightMove = value;
	else
		isblockForwardBackwardMove = value;
}