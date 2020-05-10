// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "TimePickup.generated.h"

/**
 * Custom Pickup class for the time capsules/pickups the player can collect
 */
UCLASS()
class GAMEDEVTVJAM_API ATimePickup : public APickup
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void WasCollected_Implementation() override;

protected:
	// Set the amount of extra time the pick up gives to the character (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra Time")
		float ExtraTime;
};
