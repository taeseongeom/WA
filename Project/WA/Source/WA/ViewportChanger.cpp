// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewportChanger.h"

#include "PlayerCharacter.h"
#include "PlayerCamera.h"


AViewportChanger::AViewportChanger()
{
 	PrimaryActorTick.bCanEverTick = false;

	cameraPos = FVector::ZeroVector;
	cameraRot = FRotator::ZeroRotator;
}

void AViewportChanger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AViewportChanger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		// 안전장치 없음. 캐스트 결과가 nullptr인지 확인하지 않으므로 불안전함
		// 카메라가 생성되지 않은 상태에서 해당 볼륨에 들어올 경우 크래시 예상
		Cast<APlayerCharacter>(OtherActor)->GetPlayerCamera()->ChangeViewport(cameraPos, cameraRot, true);
	}
}
void AViewportChanger::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		Cast<APlayerCharacter>(OtherActor)->GetPlayerCamera()->ChangeViewport(cameraPos, cameraRot, false);
	}
}