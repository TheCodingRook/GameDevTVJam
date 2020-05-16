// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "UnlockInteraction.h"

UUnlockInteraction::UUnlockInteraction()
{
	InteractionText = FText::FromString("Unlock").ToUpper();
}

void UUnlockInteraction::ExecuteInteraction(AGameDevTVJamCharacter* Instigator)
{
	// Not calling Super here because if unlock interaction is unavailable (e.g. due to lack of a corresponding key)
	// there is no point executing it (for now)
	// Super::ExecuteInteraction(Instigator);
	UnlockProp(Instigator);
}
