// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PuzzleVisComponent.generated.h"

/*
 * Custom class for a visual aid that shows the different elements of a puzzle (connects actors that have a PuzzleElement component
 * to the actor that has a Puzzle component and to which they are linked to)
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEVTVJAM_API UPuzzleVisComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleVisComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//~ Begin UObject interface.
	virtual void PostLoad() override;
	//virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject interface.

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

#if WITH_EDITORONLY_DATA
	// Continue showing debug information even if you deselect this actor.
	UPROPERTY(EditAnywhere, Transient, Category = "DebugFeatures", AdvancedDisplay)
	uint8 bKeepDebugDisplayOn : 1;

	// Show debug information including spheres
	UPROPERTY(Transient)
	uint8 bShowSpheres : 1;

	// Toggle sphere display on or off
	UFUNCTION(BlueprintCallable, Category = "DebugFeatures", meta = (CallInEditor = "true"))
	void ToggleSpheres();
#endif //WITH_EDITORONLY_DATA
		
};
