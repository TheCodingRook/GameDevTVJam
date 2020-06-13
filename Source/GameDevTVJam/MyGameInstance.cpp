// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MyGameInstance.h"
#include "InteractionComponentBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameDevTVJamCharacter.h"

void UMyGameInstance::PushNewInteractionCommand(UInteractionComponentBase* NewInteractionCommand)
{
	InteractionCommandStack.Add(NewInteractionCommand);
}

void UMyGameInstance::PopInteractionCommand(UInteractionComponentBase* InteractionCommandToRemove)
{
	if (InteractionCommandStack.Num() > 0)
	{
		InteractionCommandStack.RemoveSingle(InteractionCommandToRemove);
	}
}

UInteractionComponentBase* UMyGameInstance::GetLatestInteractionCommand()
{
	if (InteractionCommandStack.Num() > 0)
	{
		return InteractionCommandStack.Last();
	}
	else
	{
		return nullptr;
	}
}

void UMyGameInstance::AddTime(float ExtraTime)
{
	CountDown += ExtraTime;
}

void UMyGameInstance::ReachedSavePoint(bool bIsNewLevel, FVector SpawnOffset)
{
	AGameDevTVJamCharacter* PlayerCharacter = Cast<AGameDevTVJamCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	// Save the player's location
	LastSavePointLocation = PlayerCharacter->GetActorLocation() + SpawnOffset;
	
	// Deal with a new level savepoint
	if (bIsNewLevel)
	{
		CurrentLevel++;
		CountDown += StartingTime;
	}

	// Save all the game variables
	CountdownAtLastSavePoint = CountDown;
	SaveNumberOfKeys = PlayerCharacter->GetNumberOfKeys();
	SaveNumberOfTreasures = CurrentNumberOfTreasures;
	SaveClimbAbility = PlayerCharacter->GetCanClimb();
}

void UMyGameInstance::LoadGameData()
{
	AGameDevTVJamCharacter* PlayerCharacter = Cast<AGameDevTVJamCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	// Update/load player game data variables
	PlayerCharacter->SetCanClimb(SaveClimbAbility);
	PlayerCharacter->SetNumberOfKeys(SaveNumberOfKeys);
	PlayerCharacter->SetActorLocation(CurrentLives < StartingLives ? LastSavePointLocation : GameStartLocation);

	// Update the rest of game instance data variables
	CountDown = CountdownAtLastSavePoint;
	CurrentNumberOfTreasures = SaveNumberOfTreasures;

}

void UMyGameInstance::InitGameRules()
{
	StartingTime = 30;
	CountDown = StartingTime;
	CountdownAtLastSavePoint = StartingTime;

	StartingLives = 5;
	CurrentLives = StartingLives;

	// We probably don't need this because it is first set by Main Menu WBP
	// LastSavePointLocation = GameStartLocation;

	// Empty out the inventory
	SavePlayerInventory.Empty();
	CurrentNumberOfTreasures = 0;
	SaveNumberOfTreasures = 0;

	// Alternative for emptying inventory list (keys)
	SaveNumberOfKeys = 0;

	// Remove climbing ability
	SaveClimbAbility = false;

	// Reset the level count
	CurrentLevel = 1;
}
