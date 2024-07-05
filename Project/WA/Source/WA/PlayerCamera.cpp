// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"

#include "PlayerCharacter.h"


APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	playerCharacter = nullptr;
	speedLevel = 8.0f;

	defaultRelativeLocation = FVector::ZeroVector;
	defaultRelativeRotation = FRotator::ZeroRotator;

	relativeLocation = FVector::ZeroVector;
	relativeRotation = FRotator::ZeroRotator;

	prevRelativeLocation = FVector::ZeroVector;
	prevRelativeRotation = FRotator::ZeroRotator;

	isMovementActive = true;

	overlapCount = 0;
}

void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerCharacter && isMovementActive)
	{
		FVector target_pos = playerCharacter->GetActorLocation() + relativeLocation;
		target_pos.Z = relativeLocation.Z;	// ���� ����
		
		// ���� ���� �̵�
		SetActorLocation(FMath::Lerp(
			GetActorLocation(), 
			target_pos, 
			DeltaTime * speedLevel));

		// ȸ�� ���°� �ٸ� ������ ȸ��
		if (GetActorRotation() != relativeRotation)
		{
			SetActorRotation(FMath::Lerp(
				GetActorRotation(),
				relativeRotation,
				DeltaTime * speedLevel));
		}
	}
}

void APlayerCamera::SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	playerCharacter = Player;

	defaultRelativeLocation = RelativeLocation;
	defaultRelativeRotation = RelativeRotation;

	relativeLocation = RelativeLocation;
	relativeRotation = RelativeRotation;

	prevRelativeLocation = RelativeLocation;
	prevRelativeRotation = RelativeRotation;
}

void APlayerCamera::SetRelativeTransform(const FVector& Position, const FRotator& Rotation)
{
	relativeLocation = Position;
	relativeRotation = Rotation;
}
void APlayerCamera::BlockCameraMovement()
{
	isMovementActive = false;
}
void APlayerCamera::RevertToDefault()
{
	relativeLocation = defaultRelativeLocation;
	relativeRotation = defaultRelativeRotation;
	isMovementActive = true;
}

void APlayerCamera::ChangeViewport(const FVector& Position, const FRotator& Rotation)
{
	prevRelativeLocation = relativeLocation;
	prevRelativeRotation = relativeRotation;
	
	relativeLocation = Position;
	relativeRotation = Rotation;

	Cast<APlayerCharacter>(playerCharacter)->SetViewportDirection(-relativeLocation);

	overlapCount++;
}
void APlayerCamera::RevertViewport(const FVector& Position, const FRotator& Rotation)
{
	if (Position == relativeLocation && Rotation == relativeRotation)	// �ֿܰ��� �ִ� ViewChanger�� ȣ���� ���
	{
		if (overlapCount <= 1)	// ���� ��ȯ�� �� ���� �̷���� ���
		{
			relativeLocation = defaultRelativeLocation;
			relativeRotation = defaultRelativeRotation;
		}
		else					// ���� ��ȯ�� 2��ø �̻��� ���
		{
			relativeLocation = prevRelativeLocation;
			relativeRotation = prevRelativeRotation;
		}

		Cast<APlayerCharacter>(playerCharacter)->SetViewportDirection(-relativeLocation);
	}

	overlapCount--;
}

void APlayerCamera::SetFOV(float field_of_view)
{
	GetCameraComponent()->SetFieldOfView(field_of_view);
}
float APlayerCamera::GetFOV() const
{
	return GetCameraComponent()->FieldOfView;
}

void APlayerCamera::AddLight()
{
	UPointLightComponent* light = CreateDefaultSubobject<UPointLightComponent>(FName("Light"));
	light->InitializeComponent();
	light->SetupAttachment(RootComponent);
}
void APlayerCamera::RemoveLight()
{
	GetComponentByClass(UPointLightComponent::StaticClass())->DestroyComponent();
}