// Fill out your copyright notice in the Description page of Project Settings.

#include "WAViewportClient.h"
#include "Engine/Canvas.h"
#include "WA.h"

void UWAViewportClient::PostRender(UCanvas * Canvas)
{
	Super::PostRender(Canvas);
	if (fading)
	{
		DrawScreenFade(Canvas);
	}
}

void UWAViewportClient::ClearFade()
{
	fading = false;
}

void UWAViewportClient::Fade(const float Duration, const bool flag)
{
	UWorld* world = GetWorld();
	if (world)
	{
		if (!fading)
		{
			UE_LOG(LogTemp, Warning, TEXT("FADE"));
		}
		fading = true;
		this->toBlack = flag;
		fadeDuration = Duration;
		fadeStartTime = world->GetTimeSeconds();
	}
}

void UWAViewportClient::DrawScreenFade(UCanvas * Canvas)
{
	if (fading)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			float Time = world->GetTimeSeconds();
			fadeAlpha = FMath::Clamp((Time - fadeStartTime) / fadeDuration, 0.0f, 1.0f);

			FColor OldColor = Canvas->DrawColor;
			FLinearColor FadeColor = FLinearColor::Black;
			FadeColor.A = toBlack ? fadeAlpha : 1 - fadeAlpha;
			Canvas->DrawColor = FadeColor.ToFColor(true); // TheJamsh: "4.10 cannot convert directly to FColor, so need to use FLinearColor::ToFColor() :)
			Canvas->DrawTile(Canvas->DefaultTexture, 0, 0, Canvas->ClipX + 1000.0f, Canvas->ClipY, 0, 0, Canvas->DefaultTexture->GetSizeX() + 1000.0f, Canvas->DefaultTexture->GetSizeY());
			Canvas->DrawColor = OldColor;
		}
	}
}

float UWAViewportClient::GetFadeAlpha() const
{
	return fadeAlpha;
}
