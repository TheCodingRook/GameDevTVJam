// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * Custom class for trigger boxes in the game that include a puzzle element component
 */
UCLASS()
class GAMEDEVTVJAM_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	
public:
	AMyTriggerBox();

	UFUNCTION()
	void NotifyTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	void BeginPlay() override;

	// Puzzle Element Component for this trigger actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzle Element")
	class UPuzzleElementComponent* PuzzleElement;
	
};
