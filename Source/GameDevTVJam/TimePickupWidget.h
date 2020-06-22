// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimePickupWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API UTimePickupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void UpdateTimeText(float ExtraTime);
};
