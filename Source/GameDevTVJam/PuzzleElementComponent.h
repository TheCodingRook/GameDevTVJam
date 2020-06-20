// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleElementComponent.generated.h"

UENUM(BlueprintType)
enum class EPuzzleElementType : uint8
{
	NOSwitch UMETA(DisplayName = "Normally Open Switch"),
	Toggle UMETA(DisplayName = "Toggle Switch"),
	NOSwitch_Rotator UMETA(DisplayName = "NOp-Switch Rotator"),
	Toggle_Rotator UMETA(DisplayName = "Toggle Rotator"),
	Type_None UMETA(DisplayName = "Null type")
};

/* Custom enumeration for defining if a trigger/switch is on or off (rotators or selector types don't have on/off)
 * other actors that include the same component. The idea is that all actors that are linked through this component have to be activated together
 * (return true) in order for a puzzle to be solved.
 */
UENUM(BlueprintType)
enum class ETriggerState : uint8
{
	Off UMETA(DisplayName = "Off"),
	On UMETA(DisplayName = "On"),
	Selector UMETA(DisplayName = "Selector")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleElementTriggered, EPuzzleElementType, ElementType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleElementUnTriggered, EPuzzleElementType, ElementType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleElementActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleElementDeactivated);

/*
 * A generic base component class to implement actors as "puzzle elements" that trigger events or solve other puzzles in combination with
 * other actors that include the same component. The idea is that all actors that are linked through this component have to be activated together
 * (return true) in order for a puzzle to be solved.
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UPuzzleElementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleElementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetElementTriggeredFlag(bool InFlag);

	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementTriggered OnPuzzleElementTriggered;

	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered as off or false or closed etc.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementUnTriggered OnPuzzleElementUnTriggered;

	///////////////////////////
	// NEW VERSIONS
	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementActivated OnPuzzleElementActivated;

	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered as off or false or closed etc.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementDeactivated OnPuzzleElementDeactivated;


	// END - NEW VERSIONS
	//////////////////////////////
	UFUNCTION(BlueprintPure, Category = "Trigger")
	bool IsTriggered() const { return bIsTriggered; }

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void ToggleTrigger();

	// Set the puzzle element type (maybe best set by a constructor?) 
	UFUNCTION(BlueprintCallable, Category = "Puzzle Type")
	void SetPuzzleElementType(EPuzzleElementType InElementType);

	UFUNCTION(BlueprintPure, Category = "Puzzle Type")
	EPuzzleElementType GetPuzzleElementType() const { return PuzzleElementType; }

	// Set the puzzle element trigger state 
	UFUNCTION(BlueprintCallable, Category = "Puzzle Type")
	void SetTriggerState(ETriggerState InTriggerState);

	UFUNCTION(BlueprintPure, Category = "Puzzle Type")
	ETriggerState GetTriggerState() const { return TriggerState; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The type of puzzle element this is (as per the above enumeration class)
	UPROPERTY(EditAnywhere, Category = "Puzzle Type")
	EPuzzleElementType PuzzleElementType;

	// The state this puzzle element is in , i.e. on/off or selector (as per the above enumeration class)
	UPROPERTY(EditAnywhere, Category = "Puzzle Type")
	ETriggerState TriggerState;

private:
	// The main boolean member field that determines if this PuzzleElement is activated or not
	UPROPERTY(EditAnywhere, Category = "Trigger")
	bool bIsTriggered;
};
