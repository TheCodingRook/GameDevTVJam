// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * Custom GameInstance class to save the state of various assets that needs
 * to be preserved between savepoints as we travel back and forth to the map
 */
UCLASS()
class GAMEDEVTVJAM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PushNewInteractionCommand(class UInteractionComponentBase* NewInteraction);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PopInteractionCommand(UInteractionComponentBase* InteractionCommandToRemove);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	UInteractionComponentBase* GetLatestInteractionCommand();

	UFUNCTION(BlueprintPure, Category = "Interaction Commands")
	TArray<UInteractionComponentBase*> GetInteractionCommandStack() const { return InteractionCommandStack; }

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void AddTime(float ExtraTime);

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void AddExtraLife() { CurrentLives++; }

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void LostLife() { CurrentLives--; }

	UFUNCTION(BlueprintPure, Category = "Game Data")
	int GetCurrentLives() const { return CurrentLives; }

	UFUNCTION(BlueprintPure, Category = "Game Data")
	FVector GetLastSavePointLocation() const { return LastSavePointLocation; }

	UFUNCTION(BlueprintPure, Category = "Game Data")
	float GetCountDownAtLastSavePoint() const { return CountdownAtLastSavePoint; }

	UFUNCTION(BlueprintPure, Category = "Player Inventory")
	TArray<AActor*> GetPlayerInventory() const { return SavePlayerInventory; }

	// Alternative method for preserving number of keys between savepoints
	UFUNCTION(BlueprintPure, Category = "Player Inventory")
	int GetSaveNumberOfKeys() const { return SaveNumberOfKeys; }

	UFUNCTION(BlueprintPure, Category = "Player Inventory")
	int GetSaveNumberOfTreasures() const { return SaveNumberOfTreasures; }

	UFUNCTION(BlueprintPure, Category = "Player Inventory")
	int GetCurrentNumberOfTreasures() const { return CurrentNumberOfTreasures; }
	
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void ReachedSavePoint(bool bIsNewLevel, FVector SpawnOffset);

	// Retrieve the global game data saved in GameInstance at start (or restart) of the game
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void LoadGameData();

	// Initialize the original values of the time,life, and location related variables
	// Will also be used for resetting between new games 
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void InitGameRules();

protected:

	 // Save the very first starting location (which is not a save point)
	// because the game mode and level blueprint will need to respawn player if 
	// they die somewhere in the first level (i.e. before any known savepoints)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	FVector GameStartLocation;

	// How many seconds does player have at the beginning of each level?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Data")
	float StartingTime = 30;

	// Timer to indicate remaining time for the player to clear level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	float CountDown = StartingTime;

	// How many lives does the player have in the beginning of the game?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data")
	int StartingLives = 5;

	// How many lives does the player have at any given moment
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	int CurrentLives = StartingLives;

	// Where is the last savepoint accessed by player located?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	FVector LastSavePointLocation = GameStartLocation; // Initialize it with an invalid value first

	// What was the countdown timer when player reached last savepoint?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	float CountdownAtLastSavePoint = StartingTime;

	// Save the player's inventory list
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Point")
	TArray<AActor*> SavePlayerInventory;

	// Alternative method for the key inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Point")
	int SaveNumberOfKeys;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Point")
	int CurrentNumberOfTreasures;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Point")
	int SaveNumberOfTreasures;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	int CurrentLevel = 1;

	// Record if player has already acquired the climbing ability
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Data")
	bool SaveClimbAbility = false;

private:
	TArray<UInteractionComponentBase*> InteractionCommandStack;

};
