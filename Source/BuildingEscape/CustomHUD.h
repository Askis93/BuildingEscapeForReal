// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API ACustomHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	// This will be drawn at the center of the screen.
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* CrosshairTexture;
};
