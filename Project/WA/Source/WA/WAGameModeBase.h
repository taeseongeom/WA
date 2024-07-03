// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultPuzzle.h"
#include "RoomActor.h"
#include "WAGameModeBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	CutScene UMETA(DisplayName = "CutScene"),
	Load UMETA(DisplayName = "Load"),
	Play UMETA(DisplayName = "Play"),
	Menu UMETA(DisplayName = "Menu"),
	Clear UMETA(DisplayName = "Clear")
};

UCLASS()
class WA_API AWAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWAGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AddInitPuzzle(ADefaultPuzzle* value, int roomNum);
	void RoomReset();
	void SetRespawnPoint(FVector point);
	void ChangeRoom(int8 roomNum, FVector resPoint);
	void SetRoomSpawnPoint(int roomNum, FVector location);
	void SetCurrentRoomNum(int8 value);
	void DisableActor(AActor* target);
	void EnableActor(AActor* target);
	FVector GetRespawnPoint() const;
	EGameState GetGameState() const;
	void SetGameState(EGameState value);

	void DisplayMenu();
	void CloseMenu(int code);

private:
	void Init();
	void ShowCutScene();

private:
	//UPROPERTY 사용 불가능한데 추후 수정필요
	TMultiMap<int8, ADefaultPuzzle*> InitPuzzles;
	TArray<ARoomActor*> rooms;
	FVector respawnPoint;
	UPROPERTY(VisibleAnywhere, Category = "State")
	EGameState state;
	UPROPERTY()
	class APlayerCharacter* pc;
	UPROPERTY()
	class AWAAmbientSound* bgm;

	UPROPERTY()
	class UMenuUI* menuUI;

public:
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DebugMode;
	UPROPERTY(EditAnywhere, Category = "Debug")
	int8 DebugRoomNum;
	UPROPERTY()
	int8 CurrentRoomNum;

	int8 maxRoomNumber;

	UPROPERTY()
	FString saveSlotName;
};