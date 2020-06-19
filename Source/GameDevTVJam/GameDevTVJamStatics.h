// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameDevTVJamGameMode.h"
#include "MyGameInstance.h"
#include "GameDevTVJamCharacter.h"
#include "GameHUDWidget.h"
#include "GameDevTVJamStatics.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API UGameDevTVJamStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static class AGameDevTVJamGameMode* GetGameDevTVJamGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static class UMyGameInstance* GetMyGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AGameDevTVJamCharacter* GetGameDevTVJamCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static APlayerController* GetGameDevTVJamController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UGameHUDWidget* GetGameHUD(const UObject* WorldContextObject);
};
