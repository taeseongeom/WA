// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "WAGameModeBase.h"
#include "PlayerCamera.h"
#include "InGameUI.h"
#include "WAGameInstance.h"
#include "PlayerCharacter_AnimInstance.h"
#include "MovableBox.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"


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

	knockBack_speed = 5000.0f;
	knockBack_decrease = 0.01f;

	camera_init = false;
	viewportDirection = FVector::ForwardVector;

	has_landed = false;
	cur_dashCount = dash_count;
	cur_dashTime = 0.0f;
	cur_dashCooltime = 0.0f;

	cur_invincibleTime = 0.0f;

	blockDir_forward = false;
	blockDir_backward = false;
	blockDir_right = false;
	blockDir_left = false;

	moveStepEffect1 = nullptr;
	moveStepEffect2 = nullptr;
	jumpEffect = nullptr;
	landEffect = nullptr;
	dashEffect = nullptr;
	hitEffect = nullptr;
	dieEffect = nullptr;

	interactionRegionOverlap = 0;

	holdingBox = nullptr;

	// 입력된 정보를 CharacterMovementComponent와 연결
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

	WaGMB = (AWAGameModeBase*)(GetWorld()->GetAuthGameMode());

	animInstance = Cast<UPlayerCharacter_AnimInstance>(GetMesh()->GetAnimInstance());
	animInstance->RegisterMoveSound(moveStepEffect1, moveStepEffect2);

	Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()))->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	// ù ���� ��, ī�޶� ����
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
	
	// dash Ƚ�� ����
	if (cur_dashCount < dash_count)
	{
		has_landed = true;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), landEffect);
}

float APlayerCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (ECharacterState::KnockBack != state)
	{
		health_point -= Damage;

		// 피격
		GetCharacterMovement()->StopMovementImmediately();
		MoveDashEnd();	// state�� IDLE�� ����Ƿ�, KnockBack���� ����� ���� ����Ǿ�� ��
		state = ECharacterState::KnockBack;
		velocity = GetActorForwardVector() * -knockBack_speed;

		inGameUI->UpdateHealthBar(health_point);

		UGameplayStatics::PlaySound2D(GetWorld(), hitEffect);
	}

	// 사망
	if (health_point <= 0)
		Death();

	return health_point;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dash 발동
	if (ECharacterState::Dash == state)
	{
		AddMovementInput(GetActorForwardVector(), dash_multiplier);

		cur_dashTime += DeltaTime;
		if (cur_dashTime >= dash_time)	// Dash 종료
		{
			MoveDashEnd();
		}
	}
	// Dash 쿨타임 진행
	if (cur_dashCount < dash_count)
	{
		cur_dashCooltime += DeltaTime;
		if (cur_dashCooltime >= dash_cooldown)
		{
			if (!GetCharacterMovement()->IsFalling() || has_landed)
			{
				cur_dashCount++;
				cur_dashCooltime -= dash_cooldown;
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

		velocity *= (1.0f - (knockBack_decrease * DeltaTime * 500.0f));
		GetCharacterMovement()->AddImpulse(velocity * DeltaTime * 500.0f);
	}

	// 추락사
	if (GetActorLocation().Z < -300)
	{
		Death();
	}

	// Movable Box와 상호작용 중 추락 체크
	if (ECharacterState::BoxMoving == state && GetCharacterMovement()->IsFalling())
	{
		if (holdingBox)
			holdingBox->ForceDisconnect();

		SetBlockPlayerMoveDirection(false, false, false, false);

		ConnectWithCharacter(nullptr);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("Input Key"));
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
	case ECharacterState::BoxMoving:
		if ((!blockDir_forward && value >= 0) ||
			(!blockDir_backward && value <= 0))
		{
			velocity.X = value;
		}
		AddMovementInput(velocity.GetSafeNormal().RotateAngleAxis(viewportDirection.Rotation().Yaw, GetActorUpVector()));
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
	case ECharacterState::BoxMoving:
		if ((!blockDir_right && value >= 0) ||
			(!blockDir_left && value <= 0))
		{
			velocity.Y = value;
		}
		AddMovementInput(velocity.GetSafeNormal().RotateAngleAxis(viewportDirection.Rotation().Yaw, GetActorUpVector()));
		break;

	case ECharacterState::Shooting:
		break;
	}
}
void APlayerCharacter::MoveJump()
{
	// 이동이 금지된 방향이 없을 때 점프 가능
	if (!blockDir_forward &&
		!blockDir_backward &&
		!blockDir_right &&
		!blockDir_left)
	{
		Jump();
		UGameplayStatics::PlaySound2D(GetWorld(), jumpEffect);
	}
}
void APlayerCharacter::MoveDashBegin()
{
	if (cur_dashCount > 0 && ECharacterState::Dash != state && (!blockDir_forward && !blockDir_backward && !blockDir_right && !blockDir_left))
	{
		cur_dashTime = 0.0f;

		// 속도 증폭
		GetCharacterMovement()->MaxWalkSpeed = move_speed * dash_multiplier;
		GetCharacterMovement()->MaxAcceleration = move_accel * dash_multiplier;
		// 중력 제거
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->Velocity.Z = 0.0f;

		state = ECharacterState::Dash;

		animInstance->SetDash(true);
		UGameplayStatics::PlaySound2D(GetWorld(), dashEffect);
	}
}
void APlayerCharacter::MoveDashEnd()
{
	if (ECharacterState::Dash == state)
	{
		cur_dashCount--;
		cur_dashTime = 0.0f;
		cur_dashCooltime = 0.0f;

		// 속도 원상복귀
		GetCharacterMovement()->MaxWalkSpeed = move_speed;
		GetCharacterMovement()->MaxAcceleration = move_accel;
		// 중력 원상복귀
		GetCharacterMovement()->GravityScale = 1.0f;

		state = ECharacterState::Idle;

		animInstance->SetDash(false);
	}
}
void APlayerCharacter::Interaction()
{
	if (!(WaGMB->GetGameState() == EGameState::CutScene))
	{
		InteractionWithPuzzle.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NextCutScene"));
		UWorld* world = GetWorld();
		if (world)
		{
			UWAGameInstance* waInstance = Cast<UWAGameInstance>(world->GetGameInstance());
			if (waInstance)
			{
				if (inGameUI->NextCutScene(waInstance->GetCurrentStage()))
				{
					inGameUI->DisableCutScene();
					SetBlockPlayerMoveDirection(false, false, false, false);
					WaGMB->SetGameState(EGameState::Load);
				}
			}
		}
	}
}

void APlayerCharacter::Death()
{
	// 리셋
	WaGMB->RoomReset();
	SetActorLocation(WaGMB->GetRespawnPoint());

	health_point = 3;
	inGameUI->UpdateHealthBar(health_point);

	velocity = FVector::ZeroVector;
	SetBlockPlayerMoveDirection(false, false, false, false);

	state = ECharacterState::Idle;

	cur_invincibleTime = 0.0f;

	UGameplayStatics::PlaySound2D(GetWorld(), dieEffect);
}

void APlayerCharacter::SetCharacterState(ECharacterState cs)
{
	state = cs;
}

void APlayerCharacter::IncreaseDashCount(int increase_num)
{
	dash_count += increase_num;
	cur_dashCount = dash_count;
}
void APlayerCharacter::DecreaseDashCount(int decrease_num)
{

	if (dash_count >= 1)
	{
		dash_count -= decrease_num;
		if (cur_dashCount > dash_count)
		{
			cur_dashCount = dash_count;
			cur_dashCooltime = 0.0f;
		}
	}
}

APlayerCamera* APlayerCharacter::GetPlayerCamera() const
{
	return playerCamera;
}
void APlayerCharacter::SetViewportDirection(const FVector& Dir)
{
	viewportDirection = Dir.GetSafeNormal();
	viewportDirection.Z = 0;
}

void APlayerCharacter::SetBlockPlayerMoveDirection(bool Forward, bool Backward, bool Right, bool Left)
{
	blockDir_forward = Forward;
	blockDir_backward = Backward;
	blockDir_right = Right;
	blockDir_left = Left;

	if (Forward || Backward)
	{
		velocity.X = 0;
		GetCharacterMovement()->StopMovementImmediately();
	}
	if (Right || Left)
	{
		velocity.Y = 0;
		GetCharacterMovement()->StopMovementImmediately();
	}
}

void APlayerCharacter::SetHealthPoint(float value)
{
	health_point = value;
}
float APlayerCharacter::GetHealthPoint() const
{
	return health_point;
}
void APlayerCharacter::InitInGameUI()
{
	if (!inGameUI)
	{
		FStringClassReference tempInGameWidgetClassRef(TEXT("/Game/BluePrints/BP_InGameUI.BP_InGameUI_C"));
		if (UClass* tempInGameWidgetClass = tempInGameWidgetClassRef.TryLoadClass<UUserWidget>())
		{
			UUserWidget* tempInGameWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), tempInGameWidgetClass);
			inGameUI = Cast<UInGameUI>(tempInGameWidget);
			inGameUI->AddToViewport();
			DisplayMessage("");
		}
	}
}
void APlayerCharacter::ActivateInGameUI()
{
	if (inGameUI)
	{
		if (!inGameUI->IsInViewport())
		{
			inGameUI->AddToViewport();
		}
	}
}
void APlayerCharacter::DeactivateInGameUI()
{
	if (inGameUI)
	{
		if (inGameUI->IsInViewport())
		{
			inGameUI->RemoveFromViewport();
		}
	}
}
void APlayerCharacter::DisplayMessage(const FString& Message, float Duration)
{
	if (inGameUI)
	{
		inGameUI->DisplayText(Message, Duration);
	}
}

void APlayerCharacter::DisplayInteractionUI(bool IsShown)
{
	if (IsShown)
	{
		interactionRegionOverlap++;
	}
	else
	{
		if (interactionRegionOverlap > 0)
			interactionRegionOverlap--;
	}

	if (interactionRegionOverlap > 0)
		Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()))->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	else
		Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()))->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
}

void APlayerCharacter::StartCutScene()
{
	if (inGameUI)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			UWAGameInstance* waInstance = Cast<UWAGameInstance>(world->GetGameInstance());
			if (waInstance)
			{
				inGameUI->EnableCutScene(waInstance->GetCurrentStage());
				SetBlockPlayerMoveDirection(true, true, true, true);
				UE_LOG(LogTemp, Warning, TEXT("Enable"));
			}
			UE_LOG(LogTemp, Warning, TEXT("No Instance"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No World"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No InGameUI"));
	}
}
void APlayerCharacter::ConnectWithCharacter(AMovableBox* HoldingMovableBox)
{
	holdingBox = HoldingMovableBox;
	
	if (HoldingMovableBox)
	{
		state = ECharacterState::BoxMoving;
	}
	else
	{
		state = ECharacterState::Idle;
	}
}
