// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Camera/CameraActor.h"
#include "PlayerCamera.generated.h"

UCLASS()
class WA_API APlayerCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	APlayerCamera();

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Target")
	AActor* playerCharacter;

	UPROPERTY(EditAnywhere, Category = "Move")
	float speedLevel;

	// 기본 카메라 위치 (상대)
	FVector defaultRelativeLocation;
	// 기본 카메라 회전 (상대)
	FRotator defaultRelativeRotation;

	// 현재 카메라 위치 (상대)
	FVector relativeLocation;
	// 현재 카메라 회전 (상대)
	FRotator relativeRotation;

public:
	/// <summary>
	/// 카메라에 초기 정보를 전달합니다.
	/// </summary>
	/// <param name="Player">해당 카메라가 추적할 캐릭터 액터</param>
	/// <param name="RelativeLocation">카메라의 상대적 위치</param>
	/// <param name="RelativeRotation">카메라의 상대적 회전</param>
	void SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation);

	/// <summary>
	/// 카메라 시야를 변경합니다.
	/// </summary>
	/// <param name="Position">새로 지정할 상대적 위치</param>
	/// <param name="Rotation">새로 지정할 상대적 회전</param>
	/// <param name="IsStart">상태 변경 여부. true면 앞의 트랜스폼으로, false면 원래의 트랜스폼으로 변경</param>
	void ChangeViewport(const FVector& Position, const FRotator& Rotation, bool IsStart);
};
