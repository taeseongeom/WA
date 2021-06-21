// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultPuzzle.h"
#include "BossEntranceTrigger.generated.h"

class ABoss_Stage2;

UCLASS()
class WA_API ABossEntranceTrigger : public ADefaultPuzzle
{
	GENERATED_BODY()
	
public:	
	ABossEntranceTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InitializePuzzle() override;

private:
	UPROPERTY(EditAnywhere, Category = "Boss Entrance Directing")
	AActor* platformToRemove;
	UPROPERTY(EditAnywhere, Category = "Boss Entrance Directing")
	ABoss_Stage2* bossCharacter;		// 추후 보스가 늘어날 경우 클래스 타입 변경

	float delay;
};
