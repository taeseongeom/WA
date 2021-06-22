// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpingBomb.generated.h"

UCLASS()
class WA_API AJumpingBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	AJumpingBomb();

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<AActor> bombEffect;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float jumpHeight;

	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundBase* bombSound;

	UPROPERTY()
	class APlayerCharacter* playerCharacter;
	FVector startPos;
	FVector targetPos;
	float curTime;
	float travelTime;

	int32 jumpCount;

public:
	/// <summary>
	/// 폭탄을 발사합니다.
	/// </summary>
	/// <param name="PlayerCharacter">캐릭터에 대한 포인터. 해당 오브젝트가 캐릭터를 추적하는 데에 필요합니다.</param>
	/// <param name="TravelTime">비행 시간. 매 발사마다 동일하게 적용됩니다.</param>
	/// <param name="JumpCount">점프 횟수. 맨 처음 발사 또한 1회로 여겨집니다.</param>
	void FireBomb(APlayerCharacter* PlayerCharacter, float TravelTime, int32 JumpCount);
};
