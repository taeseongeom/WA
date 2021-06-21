// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Boss_Stage2.generated.h"

class UBoss_Stage2_Anim;
class APlayerCharacter;
class ALaserBarrel;
class AShooter;
class ABossBullet;
class ASpikeWall;
class AJumpingBomb;

DECLARE_DELEGATE(FPatternDelegate);

UENUM(BlueprintType)
enum class EBossState : uint8
{
	STEP1 UMETA(DisplayName = "Step 1"),
	STEP2 UMETA(DisplayName = "Step 2"),
	STEP3 UMETA(DisplayName = "Step 3"),
	STEP4 UMETA(DisplayName = "Step 4")
};

UCLASS()
class WA_API ABoss_Stage2 : public ACharacter
{
	GENERATED_BODY()

public:
	ABoss_Stage2();

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Health Point of the Boss Character.
	UPROPERTY(EditAnywhere, Category = "Health")
	int32 maxHealthPoint;
	// 보스의 현재 체력
	int32 healthPoint;

	// 보스 초기 위치
	FVector bossStartPosition;
	// Boss character will fight against you at this position.
	UPROPERTY(EditAnywhere, Category = "Entrance")
	FVector bossStandPosition;

	// Waiting time for the next pattern begin.
	UPROPERTY(EditAnywhere, Category = "Pattern")
	float patternInterval;

	// Collision box object to use for the region of placement laser barrel and shooter.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 1")
	AActor* laserPlaceRegion;
	// Blueprint class of Laser_Barrel object.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 1")
	TSubclassOf<ALaserBarrel> laserBarrelBlueprint;
	// Shooter blueprint class.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 1")
	TSubclassOf<AShooter> shooterBlueprint;
	// Lifetime of shooter object(as same with lasers deactive time).
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 1")
	float shooterActiveTime;
	// 현재 생성된 모든 레이저 배럴
	TArray<ALaserBarrel*> lasers;
	UPROPERTY()
	AShooter* tempShooter;

	// Collision box object to use for the region of spreaded bullets.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	AActor* bulletSpreadRegion;
	// Blueprint class of BossBullet object.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	TSubclassOf<ABossBullet> bossBulletBlueprint;
	// Initial counts of bullet.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	int32 initBulletCount;
	// 현재 총알 개수
	int32 bulletCount;
	// Increased count of bullet when each pattern passed.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	int32 bulletCountIncrease;
	// The time during bullets move to its own position.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	float bulletPlacementTime;
	// The color when before it is fired.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	FColor bulletWarningColor;
	// Interval of bullet's secondary fire.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	float bulletShotDelay;
	// Moving speed of the bullet when bullets goes fired.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 2")
	float bulletSpeed;
	// 현재 생성한 모든 총알
	TArray<ABossBullet*> bullets;
	// 현재 발사 중인 총알 인덱스. 초기화의 용이성을 위해 마지막 원소부터 시작
	int32 bulletIndex;

	// Blueprint class of SpikeWall object.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 3")
	TSubclassOf<ASpikeWall> spikeWallBlueprint;
	// World Position of the left spike wall is spawned.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 3")
	FVector spikeWallLeftSpawnPos;
	// World Position of the right spike wall is spawned.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 3")
	FVector spikeWallRightSpawnPos;
	// Spike Wall wait for this seconds before begin to move.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 3")
	float spikeWallWaitTime;
	// The time during spike wall move to destination.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 3")
	float spikeWallMoveTime;
	UPROPERTY()
	ASpikeWall* leftSpikeWall;
	UPROPERTY()
	ASpikeWall* rightSpikeWall;

	// Blueprint class of JumpingBomb object.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 4")
	TSubclassOf<AJumpingBomb> jumpingBombBlueprint;
	// Initial counts of jump. The first fire is regarded as 1 count as well.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 4")
	int32 initBombJumpCount;
	// 현재 폭탄의 점프 횟수
	int32 bombJumpCount;
	// The time during bombs move to destination.
	UPROPERTY(EditAnywhere, Category = "Pattern|Pattern 4")
	float bombMoveTime;

	// This user widget blueprint will be shown when boss dead. It is temporary.
	UPROPERTY(EditAnywhere, Category = "Temp")
	TSubclassOf<UUserWidget> gameClearUIBlueprint;

	UPROPERTY()
	UBoss_Stage2_Anim* animInstance;
	UPROPERTY()
	APlayerCharacter* playerCharacter;

	// 보스 활성화 여부. 활성화되어야 패턴을 시작
	bool activation;
	// 타이머
	float curTimer;
	// 현재 패턴 함수를 가리키는 델리게이트
	FPatternDelegate currentPattern;
	// 보스 캐릭터의 현재 상태
	EBossState state;


	UFUNCTION()
	void Entrance();
	UFUNCTION()
	void Pattern_1();
	UFUNCTION()
	void Pattern_2();
	UFUNCTION()
	void Pattern_3();
	UFUNCTION()
	void Pattern_4();

	void Death();

public:
	void Initialize();
	void Activate();
};
