// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

/*
 * Custom class to implement actors that have a 'PuzzleElement' component and can trigger other actors (that represent a puzzle to be solved)
 */

UCLASS()
class GAMEDEVTVJAM_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// When extending this function, remember to call Super and call it FIRST!
	virtual void OnTriggerActivated();

	class UPuzzleElementComponent* GetPuzzleElementComponent() const { return PuzzleElement; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// PuzzleElement Component for this trigger actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzle Element")
	UPuzzleElementComponent* PuzzleElement;

	// Sound to play when actor is activated (if any)
	UPROPERTY(EditDefaultsOnly, Category = "Setup Settings")
	class USoundBase* TriggerSound;

	// Helpful to store starting location if this trigger actor moves when activated
	UPROPERTY(BlueprintReadWrite, Category = "Setup setttings")
	FVector StartingLocation;

	// Determines whether to play a trigger sound the first time
	// Useful when things are set to trigger offscreen when game starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup settings")
	bool bMuteFirstSound;

	UFUNCTION()
	void ToggleState();
	
};
