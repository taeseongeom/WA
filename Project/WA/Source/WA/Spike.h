// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "Spike.generated.h"

UENUM(BlueprintType)
enum class ESpikeType : uint8
{
	FIXED UMETA(DisplayName = "Fixed"),
	SWITCHABLE UMETA(DisplayName = "Switchable"),
	TIMELAPSE UMETA(DisplayName = "Timelapse")
};

UCLASS()
class WA_API ASpike : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
	
public:	
	ASpike();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void InitializePuzzle() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnSwitch() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spike")
	int damage;
	UPROPERTY(EditAnywhere, Category = "Spike")
	ESpikeType spikeType;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float beginDelay;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float activePeriod;
	UPROPERTY(EditAnywhere, Category = "Spike|Timelapse")
	float deactivePeriod;

	// 가시 활성화 여부. true일 때 가시가 올라온 상태
	bool activation;

	// beginDelay 변수를 이용한 초기 작동 딜레이를 걸 것인지 여부
	bool isBegin;
	// 현재 작동 시간
	float currentTime;

	// 가시 작동 애니메이션 실행 여부
	bool playAnimation;
	// 가시 작동 애니메이션 실행 시간
	float animationTime;

	UPROPERTY()
	USceneComponent* spikeMesh;


	// 가시의 활성화 여부를 변경합니다.
	void SwitchActive(bool Active);
};
