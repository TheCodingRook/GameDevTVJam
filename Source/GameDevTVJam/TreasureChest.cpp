// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TreasureChest.h"
#include "GameDevTVJamCharacter.h"

void ATreasureChest::OnWasInteractedWith()
{
	bIsAlreadyUnlocked = true;
	bIsWidgetNecessary = false;
	Super::OnWasInteractedWith();
	
}

bool ATreasureChest::ComboQuery(AGameDevTVJamCharacter* PlayerCharacter)
{
	return PlayerCharacter->GetNumberOfKeys() > 0 ? true: false;
}
