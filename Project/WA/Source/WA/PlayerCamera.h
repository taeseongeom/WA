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

	// 이전 카메라 위치 (상대)
	FVector prevRelativeLocation;
	// 이전 카메라 회전 (상대)
	FRotator prevRelativeRotation;

	bool isMovementActive;

	// 뷰포트 체인저 중첩 수
	int overlapCount;

public:
	/// <summary>
	/// 카메라에 초기 정보를 전달합니다.
	/// </summary>
	/// <param name="Player">해당 카메라가 추적할 캐릭터 액터</param>
	/// <param name="RelativeLocation">카메라의 상대적 위치</param>
	/// <param name="RelativeRotation">카메라의 상대적 회전</param>
	void SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation);

	void SetRelativeTransform(const FVector& Position, const FRotator& Rotation);
	void BlockCameraMovement();
	/// <summary>
	/// 강제로 카메라의 시야를 원래 상태로 되돌립니다. ViewportChanger 내부에 있었을 경우 버그를 야기할 수 있습니다.
	/// </summary>
	void RevertToDefault();

	/// <summary>
	/// 카메라 시야를 변경합니다.
	/// </summary>
	/// <param name="Position">새로 지정할 상대적 위치</param>
	/// <param name="Rotation">새로 지정할 상대적 회전</param>
	void ChangeViewport(const FVector& Position, const FRotator& Rotation);
	/// <summary>
	/// 카메라 시야를 원래대로 되돌립니다.
	/// </summary>
	/// <param name="Position">ViewportChanger에 지정된 상대적 위치</param>
	/// <param name="Rotation">ViewportChanger에 지정된 상대적 회전</param>
	void RevertViewport(const FVector& Position, const FRotator& Rotation);

	void AddLight();
	void RemoveLight();
};
