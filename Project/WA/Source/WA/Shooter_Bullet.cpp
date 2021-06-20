#include "Shooter_Bullet.h"
#include "WA.h"

// Sets default values
AShooter_Bullet::AShooter_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Bullet"));
}

// Called when the game starts or when spawned
void AShooter_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

void AShooter_Bullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (!OtherActor->ActorHasTag(FName("Direction_Changer")) &&
		!OtherActor->ActorHasTag(FName("Shooter")) &&
		!OtherActor->ActorHasTag(FName("Character")))
	{
		Destroy();
	}
}

// Called every frame
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

