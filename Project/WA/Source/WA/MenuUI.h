// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

class UImage;
class UCanvasPanel;
class UProgressBar;


UCLASS()
class WA_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* img_cancle;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_volume;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_title;

	UPROPERTY(Meta = (BindWidget))
	UCanvasPanel* pan_volume;
	UPROPERTY(Meta = (BindWidget))
	UProgressBar* bar_gage;

private:
	UPROPERTY(EditAnywhere, Category="Texture")
	UTexture2D* normalSlotTexture;
	UPROPERTY(EditAnywhere, Category="Texture")
	UTexture2D* hoveredSlotTexture;

	class APlayerController* pc;
	int8 index;
	bool isVolumePanelOpen;

	class AWAAmbientSound* audio;


	void Change(int8 index);
	void Select(int8 current_index);
	void SetVolume(float volume);
};
