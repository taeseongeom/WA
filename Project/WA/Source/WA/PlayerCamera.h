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

	// �⺻ ī�޶� ��ġ (���)
	FVector defaultRelativeLocation;
	// �⺻ ī�޶� ȸ�� (���)
	FRotator defaultRelativeRotation;

	// ���� ī�޶� ��ġ (���)
	FVector relativeLocation;
	// ���� ī�޶� ȸ�� (���)
	FRotator relativeRotation;

	// ���� ī�޶� ��ġ (���)
	FVector prevRelativeLocation;
	// ���� ī�޶� ȸ�� (���)
	FRotator prevRelativeRotation;

	bool isMovementActive;

	// ����Ʈ ü���� ��ø ��
	int overlapCount;

public:
	/// <summary>
	/// ī�޶� �ʱ� ������ �����մϴ�.
	/// </summary>
	/// <param name="Player">�ش� ī�޶� ������ ĳ���� ����</param>
	/// <param name="RelativeLocation">ī�޶��� ����� ��ġ</param>
	/// <param name="RelativeRotation">ī�޶��� ����� ȸ��</param>
	void SetInitialize(AActor* Player, const FVector& RelativeLocation, const FRotator& RelativeRotation);

	void SetRelativeTransform(const FVector& Position, const FRotator& Rotation);
	void BlockCameraMovement();
	/// <summary>
	/// ������ ī�޶��� �þ߸� ���� ���·� �ǵ����ϴ�. ViewportChanger ���ο� �־��� ��� ���׸� �߱��� �� �ֽ��ϴ�.
	/// </summary>
	void RevertToDefault();

	/// <summary>
	/// ī�޶� �þ߸� �����մϴ�.
	/// </summary>
	/// <param name="Position">���� ������ ����� ��ġ</param>
	/// <param name="Rotation">���� ������ ����� ȸ��</param>
	void ChangeViewport(const FVector& Position, const FRotator& Rotation);
	/// <summary>
	/// ī�޶� �þ߸� ������� �ǵ����ϴ�.
	/// </summary>
	/// <param name="Position">ViewportChanger�� ������ ����� ��ġ</param>
	/// <param name="Rotation">ViewportChanger�� ������ ����� ȸ��</param>
	void RevertViewport(const FVector& Position, const FRotator& Rotation);

	void SetFOV(float field_of_view = 90.0f);
	float GetFOV() const;

	void AddLight();
	void RemoveLight();
};
