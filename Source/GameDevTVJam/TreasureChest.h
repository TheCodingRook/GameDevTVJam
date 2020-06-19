// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractablePropBase.h"
#include "TreasureChest.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ATreasureChest : public AInteractablePropBase
{
	GENERATED_BODY()

public:
	bool IsAlreadyUnlocked() const { return bIsAlreadyUnlocked; }
	
	void OnWasInteractedWith() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OpenLid();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void InsertKey();

	bool ComboQuery(class AGameDevTVJamCharacter* PlayerCharacter) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Interaction")
	bool bIsAlreadyUnlocked = false;
};
