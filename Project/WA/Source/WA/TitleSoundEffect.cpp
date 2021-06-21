// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleSoundEffect.h"
#include "Components/AudioComponent.h"

// Sets default values
ATitleSoundEffect::ATitleSoundEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
// Called when the game starts or when spawned
void ATitleSoundEffect::BeginPlay()
{
	Super::BeginPlay();
	audioComp = FindComponentByClass<UAudioComponent>();
	audioComp->bAutoActivate = false;
}

void ATitleSoundEffect::PlayBtnEffect(USoundBase * source)
{
	audioComp->SetSound(source);
	audioComp->Play();
}

