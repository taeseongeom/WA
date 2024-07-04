// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityGainVolume.h"

#include "PlayerCharacter.h"
#include "PlayerCamera.h"


AAbilityGainVolume::AAbilityGainVolume()
{
 	PrimaryActorTick.bCanEverTick = true;

	isUsed = false;
	isDirectingWork = false;
	directingAngle = 0.0f;
	directingVel = 0.0f;

	rotationSpeed = 60.0f;
}

void AAbilityGainVolume::BeginPlay()
{
	Super::BeginPlay();
	
	characterPosition = GetActorLocation() + FVector(0.0f, 0.0f, 88.0f);
}

void AAbilityGainVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!isUsed)
	{
		if (OtherActor->ActorHasTag(FName("Character")))
		{
			APlayerCharacter* pc = Cast<APlayerCharacter>(OtherActor);
			if (pc)
			{
				isUsed = true;

				directingAngle = 0.0f;
				directingVel = 0.0f;

				playerCharacter = pc;
				playerCam = pc->GetPlayerCamera();

				
				// ĳ���� �̵� ����
				playerCharacter->SetCharacterState(ECharacterState::CutScene);
				playerCharacter->SetBlockPlayerMoveDirection(true, true, true, true);
				playerCharacter->GetCharacterMovement()->StopMovementImmediately();
				playerCharacter->DecreaseDashCount(1);
				// ĳ���͸� �ش� ��ü�� ��ġ�� ���� �̵�
				playerCharacter->SetActorLocation(characterPosition);
				playerCharacter->SetActorRotation(FQuat(FVector::UpVector, PI*17.0f / 18.0f));
				// UI ��Ȱ��ȭ
				playerCharacter->DeactivateInGameUI();

				// ī�޶��� ���� �̵� ��� off
				playerCam->BlockCameraMovement();
				// ī�޶��� ��ġ �� ���� ���� ����
				playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 0.0f));
				playerCam->SetActorRotation((characterPosition - playerCam->GetActorLocation()).ToOrientationQuat());
				// ī�޶� ���� �ʱ�ȭ
				playerCam->SetActorRotation(FQuat::Identity);

				isDirectingWork = true;
				UGameplayStatics::PlaySound2D(GetWorld(), gatchaEffect);
			}
		}
	}
}

void AAbilityGainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDirectingWork)
	{
		CameraDirecting(DeltaTime);
	}
}

void AAbilityGainVolume::CameraDirecting(float DeltaTime)
{
	// ù 3ȸ�� "��~ �θ��Կ�~"
	if (timeline < 3.0f)
	{
		if (timeline < 1.5f)
		{
			directingVel += 480.0f * DeltaTime * DeltaTime;
		}
		else
		{
			directingVel -= 480.0f * DeltaTime * DeltaTime;
		}
		directingAngle += directingVel;
		directingAngle = FMath::Min<float>(directingAngle, 1080.0f);

		float height = FMath::Lerp<float>(0.0f, 80.0f, timeline / 3.0f);
		playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, -40.0f + height).RotateAngleAxis(directingAngle, GetActorUpVector()));

		FVector dir = characterPosition - playerCam->GetActorLocation();
		dir.Z = 0.0f;
		playerCam->SetActorRotation(dir.ToOrientationQuat());
	}
	// ��� ����
	else if (timeline < 3.2f)
	{
		if (directingVel != 0.0f)
		{
			directingVel = 0.0f;
		}
		if (directingAngle != 0.0f)
		{
			directingAngle = 0.0f;
		}
	}
	// 1ȸ��
	else if (timeline >= 3.2f && timeline < 4.2f)
	{
		directingVel = 360.0f * DeltaTime;
		directingAngle += directingVel;

		playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 40.0f).RotateAngleAxis(directingAngle, GetActorUpVector()));

		FVector dir = characterPosition - playerCam->GetActorLocation();
		dir.Z = 0.0f;
		playerCam->SetActorRotation(dir.ToOrientationQuat());
	}
	// Ŭ���� ��, ��ũ
	else if (timeline >= 4.2f && timeline < 5.0f)
	{
		FVector dist = FMath::Lerp<FVector>(playerCam->GetActorLocation(), characterPosition + FVector(-80.0f, 0.0f, 60.0f), DeltaTime * 10.0f);
		playerCam->SetActorLocation(dist);
		playerCam->SetFOV(FMath::Lerp<float>(playerCam->GetFOV(), 120.0f, DeltaTime * 10.0f));
	}
	// �ε�ε� ���� (���Ķ�)
	else if (timeline >= 5.5f && timeline < 7.5f)
	{
		float height = FMath::Sin(FMath::DegreesToRadians((timeline - 5.5f) * 1440.0f)) * 20.0f;
		playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 20.0f + height));
		playerCam->SetFOV();
	}
	// ����
	else if (timeline >= 7.5f)
	{
		isDirectingWork = false;

		// ĳ���� �̵��� UI ���� ����
		playerCharacter->SetCharacterState(ECharacterState::Idle);
		playerCharacter->SetBlockPlayerMoveDirection(false, false, false, false);
		playerCharacter->CloseMenu();
		playerCharacter->ActivateInGameUI();
		playerCharacter->DisplayMessage(noticeMessage, 5.0f);

		playerCharacter->IncreaseDashCount(1);

		//playerCam->RemoveLight();
		playerCam->RevertToDefault();

		return;
	}

	timeline += DeltaTime;
}