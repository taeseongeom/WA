// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "WAViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class WA_API UWAViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

private:
	uint32 fading : 1;
	uint32 toBlack : 1;
	float fadeAlpha;
	float fadeStartTime;
	float fadeDuration;

public:
	virtual void PostRender(UCanvas* Canvas) override;
	virtual void ClearFade();
	virtual void Fade(const float Duration, const bool flag);
	void DrawScreenFade(UCanvas* Canvas);
	float GetFadeAlpha() const;
};
