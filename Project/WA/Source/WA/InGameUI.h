// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class WA_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* img_portrait;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_interactable;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_health_0;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_health_1;
	UPROPERTY(Meta = (BindWidget))
	UImage* img_health_2;

	UPROPERTY(Meta = (BindWidget))
	UImage* img_dialog;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* txt_dialog;

	UPROPERTY(Meta = (BindWidget))
	UImage* img_cutscene;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* txt_cutscene;


	void UpdateHealthBar(int HealthPoint);

	void DisplayText(const FString& String, float Duration = 0);
	bool NextCutScene(int stage);

	void EnableCutScene(int stage);
	void DisableCutScene();
private:
	UPROPERTY(EditAnywhere, Category = "CutScene")
	TMap<FString, UTexture2D*> cutScenes;

	int cutSceneNum;
	bool isCutSceneDisplaying;
	float timer;
};
