// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityGainVolume.generated.h"

UCLASS()
class WA_API AAbilityGainVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AAbilityGainVolume();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// 해당 볼륨 작동 여부. 1회성 작동이므로 bool type check로 할지, 오브젝트 제거로 할지 정해야 함
	bool isUsed;
	// 카메라 연출이 작동하고 있는지의 여부
	bool isDirectingWork;

	float timeline;
	float directingAngle;
	float directingVel;

	FVector characterPosition;

	UPROPERTY(EditAnywhere, Category = "Directing")
	float rotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* gatchaEffect;

	UPROPERTY()
	class APlayerCharacter* playerCharacter;
	UPROPERTY()
	class APlayerCamera* playerCam;


	void CameraDirecting(float DeltaTime);
};
