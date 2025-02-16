// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleComponent.generated.h"

UENUM(BlueprintType)
enum class LogicGateType : uint8
{
	OR UMETA(DisplayName = "OR"),
	AND UMETA(DisplayName = "AND"),
	XOR UMETA(DisplayName = "XOR"),
	NAND UMETA(DisplayName = "NAND"),
	NOR UMETA(DisplayName = "NOR"),
	XNOR UMETA(DisplayName = "XNOR")
};


// Forward declarations
class UPuzzleElementComponent;

/**
 * Custom component class to designate an actor as a puzzle/riddle, that may need several other actors to trigger
 * a "condition satisfied" in order for the puzzle to be solved. The other actors should include a "PuzzleElement"
 * component to designate them as "pieces" of a puzzle (hence the name Elements)
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UPuzzleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Return the array of Actors that this actor is linked to
	UFUNCTION(BlueprintPure, Category = "Puzzle Elements")
	TArray<AActor*> GetActorsList() const { return ActorsList; }

	// Return the array of PuzzleElement object references that this actor is linked to (from the above actors' list)
	UFUNCTION(BlueprintPure, Category = "Puzzle Elements")
	TArray<UPuzzleElementComponent*> GetPuzzleElementsList() const { return PuzzleElementsList; }

	// Check to see if all the triggers / puzzle elements for this actor are satisfied
	UFUNCTION(BlueprintPure, Category = "Puzzle Elements")
	bool AreAllPuzzleElementsActive();

	LogicGateType GetLogicGateType() const { return ElementsLogic; }

	void AddPuzzleElement(UPuzzleElementComponent* NewPuzzleElement);

protected:
	// What type of logic connects the various puzzle elements?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Puzzle Elements")
	LogicGateType ElementsLogic;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// List of PuzzlElement object references from the above actors' list
	UPROPERTY(BlueprintReadWrite, Category = "Puzzle Elements")
	TArray<UPuzzleElementComponent*> PuzzleElementsList;

private:
	// List of actors that will be the puzzle elements that this actor is linked to as part of a puzzle
	UPROPERTY(EditAnywhere, Category = "Puzzle Elements")
	TArray<AActor*> ActorsList;

	
};
