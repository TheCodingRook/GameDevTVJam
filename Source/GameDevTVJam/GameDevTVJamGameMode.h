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

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlayerLost();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlayerWon();

	class UGameHUDWidget* GetGameHUD() const { return GameHUD; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameHUDWidget> GameHUDClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UPauseMenuWidget> PauseMenuClass;

	/** Music sound to loop during game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* GameMusic;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	class UAudioComponent* GameMusicAudioComponent;

	/** Music to play when player wins */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	USoundBase* VictoryMusic;
	UAudioComponent* VictoryMusicAudioComponent;

	void BeginPlay() override;

private:
	class AGameDevTVJamCharacter* PlayerCharacter;
	class UMyGameInstance* GameInstance;

	UGameHUDWidget* GameHUD;
	UPauseMenuWidget* PauseMenu;

	/** Member fields to control if Tick function can update the game's timer in the HUD */
	bool bCanUpdateTimer = true;
	int FrameDelay = 1;
	int FrameCount = 0;
	float ElapsedTime = 0;

	// Helper function to allow a delay before restarting game after death
	void RestartGame_HelperFunc();
};
