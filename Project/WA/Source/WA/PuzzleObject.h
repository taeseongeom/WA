// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzleObject.generated.h"

UCLASS()
class WA_API APuzzleObject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APuzzleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Player instance. It MUST be set to bind this actor's function with player's interaction function.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Binding")
	class APlayerPawn* m_Player;

	// The size of box region that recognize overlapping to interact.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Region")
	FVector boxExtent;

	// Whether interaction region gizmo is shown or not on game. It is false by default.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Region")
	bool isShow;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool jumping;

	FVector velocity;

	int num_overlappingObj;


	// Be excuted by pressing interaction key.
	UFUNCTION()
	void Interaction();
};
