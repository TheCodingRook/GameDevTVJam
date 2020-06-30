// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TriggerableActor.h"
#include "PuzzleElementComponent.h"
#include "SpikeTrap.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ASpikeTrap : public ATriggerableActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Trap Settings")
	void SpringTrap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Trap Settings")
	void ResetTrap();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trap Settings")
	void DeathFromAboveTrap(EPuzzleElementType PuzzleElementType);

	void BeginPlay() override;

	void OnTriggered() override;

	UFUNCTION()
	void NotifySpikeTrapBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Trap settings")
		bool bIsActive;

	UPROPERTY(EditAnywhere, Category = "Trap settings")
	bool bIsDeathFromAboveTrap;

	// How much to open the door by (vertical movement intended here)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap settings")
	float TrapZOffset;

	// How fast the trap springs (playrate setting for blueprint Timeline node)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap settings")
	float TrapSpringRate = 1;

	// How fast the trap resets (playrate setting for blueprint Timeline node)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap settings")
	float TrapResetRate = 1;

	// Specific sound for the 'Death From Above' version of this trap
	UPROPERTY(EditDefaultsOnly, Category = "Trap settings")
	class USoundBase* DeathFromAboveSound;

	// Attempts to either close or open door depending on the elements that triggered it
	UFUNCTION()
	void AttemptOperateTrap(EPuzzleElementType PuzzleElementType);
};
