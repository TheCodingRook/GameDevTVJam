// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ChestKey.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API AChestKey : public APickup
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void NotifyKeyBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
protected:
	void BeginPlay() override;
};
