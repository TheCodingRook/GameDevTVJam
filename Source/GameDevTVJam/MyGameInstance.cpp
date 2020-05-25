// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MyGameInstance.h"
#include "InteractionComponentBase.h"

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

	// Alternative for emptying inventory list
	SaveNumberOfKeys = 0;

	CurrentNumberOfTreasures, SaveNumberOfTreasures =  0;
}
