// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBullet.h"


ABossBullet::ABossBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	damage = 1;
	
	InitializeData();
}

void ABossBullet::BeginPlay()
{
	Super::BeginPlay();
	
	mesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
}

void ABossBullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (OtherActor->ActorHasTag(FName("Character")))
	{
		OtherActor->TakeDamage(damage, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
		Destroy();
	}
}

void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		curTime += DeltaTime;

		if (!targetPos.IsZero())		// MoveToLocation의 경우
		{
			float rate = curTime / travelTime;

			if (rate < 1)
				SetActorLocation(FMath::Lerp<FVector>(startPos, targetPos, rate));
			else
				InitializeData();
		}
		else if (!targetDir.IsZero())	// MoveToDirection의 경우
		{
			SetActorLocation(GetActorLocation() + targetDir * speed * DeltaTime);
		}
	}
}

void ABossBullet::InitializeData()
{
	isMoving = false;

	startPos = FVector::ZeroVector;
	targetPos = FVector::ZeroVector;
	targetDir = FVector::ZeroVector;

	curTime = 0;
	travelTime = 0;
	speed = 0;
}

void ABossBullet::MoveToLocation(const FVector& Destination, float TravelTime)
{
	InitializeData();
	
	isMoving = true;
	
	startPos = GetActorLocation();
	targetPos = Destination;

	travelTime = TravelTime;
}
void ABossBullet::MoveToDirection(const FVector& Direction, float Speed, float LifeTime)
{
	InitializeData();
	
	isMoving = true;

	targetDir = Direction.GetSafeNormal();
	targetDir.Z = 0.0f;

	speed = Speed;

	if (LifeTime > 0)
		SetLifeSpan(LifeTime);
}

void ABossBullet::ChangeColor(const FColor& Color)
{
	if (mesh)
	{
		UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(
			mesh->GetMaterial(0),
			NULL);

		mat->SetVectorParameterValue(FName("Color"), FLinearColor(Color));
		mesh->SetMaterial(0, mat);
	}
}