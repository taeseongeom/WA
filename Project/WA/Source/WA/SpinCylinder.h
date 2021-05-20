#pragma once

#include "CoreMinimal.h"
#include "DefaultPuzzle.h"
#include "Switchable.h"
#include "SpinCylinder.generated.h"

UCLASS()
class WA_API ASpinCylinder : public ADefaultPuzzle, public ISwitchable
{
	GENERATED_BODY()
public:
	ASpinCylinder();
private:
	UPROPERTY(EditAnywhere, Category = "Init")
	bool isTurnLeft;
	UPROPERTY(EditAnywhere, Category = "Init")
	float turnSpeed;

	float moveDir;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void OnSwitch() override;
};
