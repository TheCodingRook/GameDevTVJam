// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponentBase.h"
#include "UnlockInteraction.generated.h"

/**
 * Custom component class to implement unlocking functionality for props that have a key/lock relationship
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UUnlockInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()

protected:
	UUnlockInteraction();
	virtual void ExecuteInteraction(AGameDevTVJamCharacter* Instigator) override;
};
