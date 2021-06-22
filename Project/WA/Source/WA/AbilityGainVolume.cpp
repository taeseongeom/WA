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

				
				// 캐릭터 이동 제한
				playerCharacter->SetBlockPlayerMoveDirection(true, true, true, true);
				playerCharacter->GetCharacterMovement()->StopMovementImmediately();
				playerCharacter->DecreaseDashCount(1);
				// 캐릭터를 해당 객체의 위치로 강제 이동
				playerCharacter->SetActorLocation(characterPosition);
				playerCharacter->SetActorRotation(FQuat::Identity + FQuat(0.0f, 0.0f, 180.0f, 0.0f));
				// UI 비활성화
				playerCharacter->DeactivateInGameUI();

				// 카메라의 기존 이동 방식 off
				playerCam->BlockCameraMovement();
				// 카메라의 위치 및 각도 강제 조정
				playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 0.0f));
				playerCam->SetActorRotation((characterPosition - playerCam->GetActorLocation()).ToOrientationQuat());
				// 카메라 시점 초기화
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
	// 첫 3회전 "자~ 부를게요~"
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
	// 잠시 멈춤
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
	// 1회전
	else if (timeline >= 3.2f && timeline < 4.2f)
	{
		directingVel = 360.0f * DeltaTime;
		directingAngle += directingVel;

		playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 40.0f).RotateAngleAxis(directingAngle, GetActorUpVector()));

		FVector dir = characterPosition - playerCam->GetActorLocation();
		dir.Z = 0.0f;
		playerCam->SetActorRotation(dir.ToOrientationQuat());
	}
	// 클로즈 업, 윙크
	else if (timeline >= 4.2f && timeline < 5.0f)
	{
		FVector dist = FMath::Lerp<FVector>(playerCam->GetActorLocation(), characterPosition + FVector(-50.0f, 0.0f, 80.0f), DeltaTime * 10.0f);
		playerCam->SetActorLocation(dist);
	}
	// 부들부들 떨기 (휘파람)
	else if (timeline >= 5.5f && timeline < 7.5f)
	{
		float height = FMath::Sin(FMath::DegreesToRadians((timeline - 5.5f) * 1440.0f)) * 20.0f;
		playerCam->SetActorLocation(characterPosition + FVector(-200.0f, 0.0f, 20.0f + height));
	}
	// 종료
	else if (timeline >= 7.5f)
	{
		isDirectingWork = false;

		// 캐릭터 이동과 UI 원상 복귀
		playerCharacter->SetBlockPlayerMoveDirection(false, false, false, false);
		playerCharacter->ActivateInGameUI();

		playerCharacter->IncreaseDashCount(1);

		//playerCam->RemoveLight();
		playerCam->RevertToDefault();

		return;
	}

	timeline += DeltaTime;
}