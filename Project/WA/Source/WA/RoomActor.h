// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"

USTRUCT()
struct FRoomData
{
	GENERATED_BODY()
public:
	bool isClear;
	TMap<FString, FVector> boxLocations;
	TMap<FString, bool> isOnSwitchs;
};

UCLASS()
class WA_API ARoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

	int GetRoomNumber() const;
	bool InitRoom();
	bool CheckClearList();
	void SaveRoom();
	void LoadRoom();
	void SetClear(bool value);
	bool GetClear() const;
	FVector GetRoomSpawnPoint() const;
	void SetRoomSpawnPoint(FVector location);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitPuzzleActors(AActor* actor);
private:
	UPROPERTY(EditAnywhere, Category = "Clear")
	TArray<class ADefaultPuzzle*> checklist;
	UPROPERTY(VisibleAnywhere, Category = "Property")
	bool isClear;
	UPROPERTY(EditAnywhere, Category = "Property")
	int roomNumber;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> boxActors;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> switchActors;
	UPROPERTY()
	FVector spawnPoint;
};
