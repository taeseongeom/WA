// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Stage2.h"

#include "PlayerCharacter.h"
#include "LaserBarrel.h"
#include "Shooter.h"
#include "BossBullet.h"
#include "SpikeWall.h"
#include "JumpingBomb.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"


ABoss_Stage2::ABoss_Stage2()
{
 	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Boss"));

	healthPoint = 5;
	patternInterval = 1.0f;

	laserPlaceRegion = nullptr;
	laserBarrelBlueprint = nullptr;
	shooterBlueprint = nullptr;
	shooterActiveTime = 5.0f;
	tempShooter = nullptr;

	bulletSpreadRegion = nullptr;
	bossBulletBlueprint = nullptr;
	bulletCount = 6;
	bulletCountIncrease = 2;
	bulletPlacementTime = 1.5f;
	bulletWarningColor = FColor::Red;
	bulletShotDelay = 0.5f;
	bulletSpeed = 2000.0f;
	bulletIndex = 0;

	spikeWallBlueprint = nullptr;
	spikeWallLeftSpawnPos = FVector(0.0f, 0.0f, 0.0f);
	spikeWallRightSpawnPos = FVector(0.0f, 0.0f, 0.0f);
	spikeWallWaitTime = 2.0f;
	spikeWallMoveTime = 5.0f;
	leftSpikeWall = nullptr;
	rightSpikeWall = nullptr;

	jumpingBombBlueprint = nullptr;
	bombJumpCount = 1;
	bombMoveTime = 2.0f;

	playerCharacter = nullptr;

	currentPattern.BindUFunction(this, FName("Pattern_1"));
	state = EBossState::STEP1;
	curTimer = 2.0f;
}

void ABoss_Stage2::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<APlayerCharacter> iter(GetWorld()); iter; ++iter)
	{
		playerCharacter = *iter;
		break;
	}
}

float ABoss_Stage2::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	healthPoint -= (int32)Damage;

	if (healthPoint <= 0)
		Death();

	return (float)healthPoint;
}

void ABoss_Stage2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (curTimer > 0)
		curTimer -= DeltaTime;
	else
		currentPattern.ExecuteIfBound();
}

void ABoss_Stage2::AppearanceDirecting()
{
	// 등장연출
}

void ABoss_Stage2::Pattern_1()
{
	/*
	* 1. 존재하는 모든 LaserBarrel을 비활성화
	* 2. 무작위 위치에 Shooter와 LaserBarrel을 각각 1개 설치
	* 3. 일정 시간 이후 Shooter를 제거하고, 모든 LaserBarrel을 활성화
	* @ 무작위 위치에 생성되는 Shooter와 LaserBarrel은 이미 생성된 구조물의 일정 범위 내에 위치해서는 안 된다.
	*/

	switch (state)
	{
	case EBossState::STEP1:
		if (laserPlaceRegion && laserBarrelBlueprint && shooterBlueprint)
		{
			for (int32 i = 0; i < lasers.Num(); i++)
			{
				lasers[i]->SwitchActive(false);
			}

			int32 limit_try = 0;
			FVector region_pos = Cast<UBoxComponent>(laserPlaceRegion->GetComponentByClass(UBoxComponent::StaticClass()))->GetComponentLocation();
			FVector region_box = Cast<UBoxComponent>(laserPlaceRegion->GetComponentByClass(UBoxComponent::StaticClass()))->GetScaledBoxExtent();
			FVector spawn_pos;
			FHitResult hit;
			do
			{
				spawn_pos = FVector(
					FMath::FRandRange(region_pos.X - region_box.X, region_pos.X + region_box.X),
					FMath::FRandRange(region_pos.Y - region_box.Y, region_pos.Y + region_box.Y),
					0.0f);

				limit_try++;
				if (limit_try > 10000)
					break;

			} while (GetWorld()->LineTraceSingleByChannel(hit, spawn_pos + FVector(0, 0, 500.0f), spawn_pos, ECollisionChannel::ECC_GameTraceChannel4));
			if (limit_try <= 10000)
			{
				lasers.Add(GetWorld()->SpawnActor<ALaserBarrel>(laserBarrelBlueprint, spawn_pos, FRotator::ZeroRotator));
			}

			limit_try = 0;
			do
			{
				spawn_pos = FVector(
					FMath::FRandRange(region_pos.X - region_box.X, region_pos.X + region_box.X),
					FMath::FRandRange(region_pos.Y - region_box.Y, region_pos.Y + region_box.Y),
					0.0f);

				limit_try++;
				if (limit_try > 10000)
					break;

			} while (GetWorld()->LineTraceSingleByChannel(hit, spawn_pos + FVector(0, 0, 500.0f), spawn_pos, ECollisionChannel::ECC_GameTraceChannel4));
			if (limit_try <= 10000)
			{
				tempShooter = GetWorld()->SpawnActor<AShooter>(shooterBlueprint, spawn_pos + FVector(0, 0, 88.0f), FRotator::ZeroRotator);
				tempShooter->SetUsageLimit(1);
			}
				
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("There are properties that is not assinged."));
		}

		curTimer = shooterActiveTime;
		state = EBossState::STEP2;
		break;

	case EBossState::STEP2:
		for (int32 i = 0; i < lasers.Num(); i++)
		{
			lasers[i]->SwitchActive(true);
		}

		if (tempShooter)
			tempShooter->Destroy();

		// 다음 패턴으로 전환
		curTimer = patternInterval;
		state = EBossState::STEP1;
		currentPattern.Unbind();
		currentPattern.BindUFunction(this, FName("Pattern_2"));
		break;
	}
}
void ABoss_Stage2::Pattern_2()
{
	/*
	* 1. 대충 오른 팔에서 랜덤한 위치에 Bullet을 흩뿌림
	* 2. 무작위 순서로 각 Bullet이 캐릭터를 향해 빠르게 날아감
	* @ 총알은 기존 6개 발사이며, 패턴을 보는 횟수에 따라 2개씩 늘어난다.
	*/

	switch (state)
	{
	case EBossState::STEP1:
		if (bulletSpreadRegion && bossBulletBlueprint)
		{
			bullets.Empty(bulletCount);
			
			FVector region_pos = Cast<UBoxComponent>(bulletSpreadRegion->GetComponentByClass(UBoxComponent::StaticClass()))->GetComponentLocation();
			FVector region_box = Cast<UBoxComponent>(bulletSpreadRegion->GetComponentByClass(UBoxComponent::StaticClass()))->GetScaledBoxExtent();
			FVector target_pos;
			for (int32 i = 0; i < bulletCount; i++)
			{
				target_pos = FVector(
					FMath::FRandRange(region_pos.X - region_box.X, region_pos.X + region_box.X),
					FMath::FRandRange(region_pos.Y - region_box.Y, region_pos.Y + region_box.Y),
					88.0f);

				ABossBullet* bullet = GetWorld()->SpawnActor<ABossBullet>(bossBulletBlueprint, GetActorLocation() + FVector(0, 0, 88.0f), FRotator::ZeroRotator);
				if (bullet)
				{
					bullet->MoveToLocation(target_pos, bulletPlacementTime);
					bullets.Add(bullet);
				}
				else
					UE_LOG(LogTemp, Error, TEXT("Spawn bullet has failed."));
			}

			bulletIndex = bullets.Num() - 1;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("There are properties that is not assinged."));
		}

		curTimer = bulletPlacementTime + bulletShotDelay;
		state = EBossState::STEP2;
		break;

	case EBossState::STEP2:
		if (bulletIndex >= 0)
			bullets[bulletIndex]->ChangeColor(bulletWarningColor);

		curTimer = bulletShotDelay;
		state = EBossState::STEP3;
		break;

	case EBossState::STEP3:
		if (bulletIndex >= 0)
		{
			bullets[bulletIndex]->MoveToDirection(
				playerCharacter->GetActorLocation() - bullets[bulletIndex]->GetActorLocation(), 
				bulletSpeed, 
				5.0f);

			bulletIndex--;
			state = EBossState::STEP2;
		}
		else
		{
			bulletIndex = 0;
			state = EBossState::STEP4;
		}
		break;

	case EBossState::STEP4:
		bulletCount += bulletCountIncrease;
		bullets.Empty(bulletCount);

		// 다음 패턴으로 전환
		curTimer = patternInterval;
		state = EBossState::STEP1;
		currentPattern.Unbind();
		currentPattern.BindUFunction(this, FName("Pattern_3"));
		break;
	}
}
void ABoss_Stage2::Pattern_3()
{
	/*
	* 1. 지형 전체를 덮을 가시 장벽을 양쪽에 생성. 단, 가시 장벽은 무작위 위치에 가시가 없다.
	* 2. 일정 시간 후 가시 장벽은 지형을 가로질러 반대편 장벽이 생성된 위치로 이동하여 소멸
	*/

	switch (state)
	{
	case EBossState::STEP1:
		if (spikeWallBlueprint && !spikeWallLeftSpawnPos.IsZero() && !spikeWallRightSpawnPos.IsZero())
		{
			leftSpikeWall = GetWorld()->SpawnActor<ASpikeWall>(spikeWallBlueprint, spikeWallLeftSpawnPos, FRotator(0, 90.0f, 0));
			rightSpikeWall = GetWorld()->SpawnActor<ASpikeWall>(spikeWallBlueprint, spikeWallRightSpawnPos, FRotator(0, 270.0f, 0));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("There are properties that is not assinged."));
		}

		curTimer = spikeWallWaitTime;
		state = EBossState::STEP2;
		break;

	case EBossState::STEP2:
		if (leftSpikeWall && rightSpikeWall)
		{
			leftSpikeWall->MoveTo(spikeWallRightSpawnPos, spikeWallMoveTime);
			rightSpikeWall->MoveTo(spikeWallLeftSpawnPos, spikeWallMoveTime);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spike Walls are not spawned."));
		}

		curTimer = patternInterval + spikeWallMoveTime;
		state = EBossState::STEP1;
		currentPattern.Unbind();
		currentPattern.BindUFunction(this, FName("Pattern_4"));
		break;
	}
}
void ABoss_Stage2::Pattern_4()
{
	/*
	* 1. 캐릭터의 위치로 하나의 폭탄을 포물선으로 발사
	* 2. 착탄한 폭탄은 즉시 폭발
	* 3. 패턴 발동 횟수에 따라 폭발 위치에서 다시 발사-폭발 메커니즘 반복
	*/

	switch (state)
	{
	case EBossState::STEP1:
		if (jumpingBombBlueprint)
		{
			AJumpingBomb* bomb = GetWorld()->SpawnActor<AJumpingBomb>(jumpingBombBlueprint, GetActorLocation(), FRotator::ZeroRotator);
			bomb->FireBomb(playerCharacter, bombMoveTime, bombJumpCount);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("There are properties that is not assinged."));
		}

		curTimer = bombMoveTime * bombJumpCount;
		state = EBossState::STEP2;
		break;

	case EBossState::STEP2:
		bombJumpCount++;

		curTimer = patternInterval;
		state = EBossState::STEP1;
		currentPattern.Unbind();
		currentPattern.BindUFunction(this, FName("Pattern_1"));
		break;
	}
}

void ABoss_Stage2::Death()
{
	currentPattern.Unbind();

	for (int32 i = 0; i < lasers.Num(); i++)
		lasers[i]->Destroy();
	lasers.Empty();

	if (tempShooter)
		tempShooter->Destroy();

	for (int32 i = 0; i < bullets.Num(); i++)
		bullets[i]->Destroy();
	bullets.Empty();
	
	Destroy();
}