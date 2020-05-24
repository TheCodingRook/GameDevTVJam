// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
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

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void AddTime(float ExtraTime);

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void AddExtraLife() { CurrentLives++; }

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void LostLife() { CurrentLives--; }

	UFUNCTION(BlueprintPure, Category = "Game Rules")
	int GetCurrentLives() const { return CurrentLives; }

	UFUNCTION(BlueprintPure, Category = "Game Rules")
	FVector GetLastSavePointLocation() const { return LastSavePointLocation; }

	UFUNCTION(BlueprintPure, Category = "Game Rules")
	float GetCountDownAtLastSavePoint() const { return CountdownAtLastSavePoint; }

	UFUNCTION(BlueprintPure, Category = "Save Point")
	TArray<AActor*> GetPlayerInventory() const { return SavePlayerInventory; }

protected:
	// Timer to indicate remaining time for the player to clear level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Rules")
		float CountDown;

	// How many seconds does player have at the beginning of each level?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Rules")
		float StartingTime = 30;

	// How many lives does the player have in the beginning of the game?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
		int StartingLives = 5;

	// How many lives does the player have at any given moment
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Rules")
		int CurrentLives;

	// Where is the last savepoint accessed by player located?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Rules")
		FVector LastSavePointLocation;

	// What was the countdown timer when player reached last savepoint?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Rules")
		float CountdownAtLastSavePoint;

	// Save the player's inventory list
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Point")
		TArray<AActor*> SavePlayerInventory;

private:
	TArray<UInteractionComponentBase*> InteractionCommandStack;

};
