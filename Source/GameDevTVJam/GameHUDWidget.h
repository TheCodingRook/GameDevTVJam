// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.generated.h"

/**
 * Custom base class for the main game's HUD
 */
UCLASS()
class GAMEDEVTVJAM_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateRemainingTime(float NewTime);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void TimesUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateRemainingLives(int NewLives);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateKeysFound(int NewKeys);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateTreasuresFound(int NewTreasures);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateCurrentLevel(int NewLevel);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void PlayDeathAnimations();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void PlayVictoryAnimation();
};
