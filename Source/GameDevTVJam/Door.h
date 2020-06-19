// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TriggerableActor.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ADoor : public ATriggerableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Door movement")
	void OpenDoor();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Door movement")
	void CloseDoor();

	void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Door movement")
	bool bIsOpen;

	// How much to open the door by (vertical movement intended here)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door movement")
	float DoorZOffset;

	// Attempts to either close or open door depending on the elements that triggered it
	UFUNCTION()
	void AttemptOperateDoor();

	//TEMPORARY DELETE AFTERWARDS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door movement")
	TArray<AActor*> PuzzleElementPlaceHolder;
};
