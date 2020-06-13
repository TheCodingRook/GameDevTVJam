// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameDevTVJamGameMode.generated.h"

UCLASS(minimalapi)
class AGameDevTVJamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameDevTVJamGameMode();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void PauseGame();


};
