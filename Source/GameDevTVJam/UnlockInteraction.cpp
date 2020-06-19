// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "UnlockInteraction.h"
#include "TreasureChest.h"
#include "GameDevTVJamStatics.h"

UUnlockInteraction::UUnlockInteraction()
{
	InteractionText = FText::FromString("Unlock").ToUpper();
}

void UUnlockInteraction::ExecuteInteraction(AGameDevTVJamCharacter* Instigator)
{
	ATreasureChest* ChestToUnlock = Cast<ATreasureChest>(GetOwner());
	if (ChestToUnlock)
	{
		if (!ChestToUnlock->IsAlreadyUnlocked() && ChestToUnlock->ComboQuery(Instigator))
		{
			// Unlock the chest and call the events for Blueprint
			ChestToUnlock->InsertKey();
			ChestToUnlock->OpenLid();

			//~ Update Game Instance with the necessary data
			int UpdatedTreasures = UGameDevTVJamStatics::GetMyGameInstance(this)->GetCurrentNumberOfTreasures() + 1;
			UGameDevTVJamStatics::GetMyGameInstance(this)->SetNumberOfTreasures(UpdatedTreasures);

			int UpdatedKeys = UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)->GetNumberOfKeys() - 1;
			UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)->SetNumberOfKeys(UpdatedKeys);

			UGameDevTVJamStatics::GetGameHUD(this)->UpdateTreasuresFound(UpdatedTreasures);
			UGameDevTVJamStatics::GetGameHUD(this)->UpdateKeysFound(UpdatedKeys);

			Super::ExecuteInteraction(Instigator);
		}
	}
}
