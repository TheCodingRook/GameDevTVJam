// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponentBase.h"
#include "GrabInteraction.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UGrabInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()
	
protected:
	UGrabInteraction();

	virtual void ExecuteInteraction(AGameDevTVJamCharacter* Instigator) override;
};
