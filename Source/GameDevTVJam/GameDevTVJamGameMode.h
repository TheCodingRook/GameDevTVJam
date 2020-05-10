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

	UFUNCTION(BlueprintCallable, Category = "Game Time")
		void AddTime(float ExtraTime);

protected:
	// How many seconds does player have?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Time")
		float CountDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Time")
		float StartingTime;


};
