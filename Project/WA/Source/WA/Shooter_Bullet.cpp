#include "Shooter_Bullet.h"
#include "WA.h"


AShooter_Bullet::AShooter_Bullet()
{
 	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Bullet"));
}

void AShooter_Bullet::BeginPlay()
{
	Super::BeginPlay();

	// Set life time(10sec)
	SetLifeSpan(10.0f);
}

void AShooter_Bullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (!OtherActor->ActorHasTag(FName("Direction_Changer")) &&
		!OtherActor->ActorHasTag(FName("Shooter")) &&
		!OtherActor->ActorHasTag(FName("Character")) &&
		!OtherActor->ActorHasTag(FName("Viewport_Changer")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion,
			GetActorLocation(), GetActorRotation());
		Destroy();
	}

	if (OtherActor->ActorHasTag(FName("Boss")))
	{
		OtherActor->TakeDamage(1, FDamageEvent(), nullptr, this);
	}
}

void AShooter_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AShooter_Bullet::SetStack(float _Speed, int _Crash_count)
{
	this->Speed = _Speed;
	this->Crash_count = _Crash_count;
}

