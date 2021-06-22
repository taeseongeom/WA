// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class WA_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Meta = (BindWidget))
	class UImage* firstSaveDataBtn;

	UPROPERTY(Meta = (BindWidget))
	class UImage* secondSaveDataBtn;

	UPROPERTY(Meta = (BindWidget))
	class UImage* thirdSaveDataBtn;

	UPROPERTY(Meta = (BindWidget))
	class UImage* quitBtn;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* pressAnyKeyText;

	UPROPERTY(Meta = (BindWidget))
	class UImage* backGround;

private:
	UPROPERTY()
	class APlayerController* pc;

	UPROPERTY(EditAnywhere, Category = "Init")
		class UTexture2D* normalSlotTexture;

	UPROPERTY(EditAnywhere, Category = "Init")
		class UTexture2D* hoveredSlotTexture;

	UPROPERTY(EditAnywhere, Category = "Init")
		class UTexture2D* normalQuitTexture;

	UPROPERTY(EditAnywhere, Category = "Init")
		class UTexture2D* hoveredQuitTexture;

	UPROPERTY(EditAnywhere, Category = "Init")
		class USoundBase* changeBtnEffect;

	UPROPERTY(EditAnywhere, Category = "Init")
		class USoundBase* quitBtnEffect;

	UPROPERTY(EditAnywhere, Category = "Init")
		class USoundBase* startBtnEffect;

	UPROPERTY()
	class ATitleSoundEffect* effectComp;

	bool isPressed;
	bool isSelectingData;
	bool isGameStart;
	int8 isIncreaseAlpha;
	int slotIndex;
	UPROPERTY()
	float alpha;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

private:
	void ChangeSlotImage(int slotIndex);
	void StartGameFromSaveData();
};
