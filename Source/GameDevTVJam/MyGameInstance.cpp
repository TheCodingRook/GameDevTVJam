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