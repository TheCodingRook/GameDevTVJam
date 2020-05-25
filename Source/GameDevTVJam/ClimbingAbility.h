// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimbingAbility.generated.h"

/**
 * Custom class to implement climbing for characters 
 */

UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UClimbingAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClimbingAbility();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Climbing")
	void Climb();

	UFUNCTION(BlueprintCallable, Category = "Climbing")
	void ClimbLedge();

	UFUNCTION(BlueprintCallable, Category = "Climbing")
	void FinishClimbing();

	UFUNCTION(BlueprintPure, Category = "Climbing")
	FVector GetLocationAfterClimbing() const { return LocationAfterClimb; }

	UFUNCTION(BlueprintPure, Category = "Climbing")
	FRotator GetRotationAfterClimbing() const { return RotationAfterClimb; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// How far in front of us can we detect climbable ledges/walls?
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float ClimbProximity = 75;

	// Radius of climbing detection sphere when facing forward (i.e. how high up can we detect ledges?)
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float ClimbDetectRadius = 20.f;

	// Manual Z offset adjustment for wall tracer (e.g. to avoid climbing really short blocks)
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float WallTraceZOffset = 50.f;

	// Vertical offset from Player's center for secondary trace to detect ledge height
	// It does not get affected by WallTraceZOffset value
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float VerticalOffset = 145; 

	// How much farther do we trace to detect gaps above the wall?
	// This loosely correlates to the capsule's radius, i.e. we want to be 
	// able to fit the character on the ledge he is climbing up to
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float GapTracerOffset = 85;

	// Adjust the vertical positioning of capsule when character hangs from ledge
	UPROPERTY(EditAnywhere, Category = "Climbing Configuration")
	float ManualZOffsetOverride;

	// Manual override of character capsule's halfheight to enable the capsule to follow character during climb
	UPROPERTY(EditAnywhere, Category = "Climbing Configuration")
	float CapsuleHalfHeightOverride = 45.f;

	// Manual override of character capsule's radius to enable the capsule to follow character during climb
	UPROPERTY(EditAnywhere, Category = "Climbing Configuration")
	float CapsuleRadiusOverride = 30.f;

	// Manually adjust the mesh positioning within the capsule to avoid collision with ledge when climbing over
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing Configuration")
	FVector ManualMeshOffset {0.f, 0.f, -60.f};

private:
	// Private member to store the pointer to the player character
	class AGameDevTVJamCharacter* OwnerCharacter;

	// Store the location of FlatSurfaceTrace hit so that we know where to place character after climbing
	FVector LocationAfterClimb;
		
	// Store the proper rotation value so that we know where to rotate character after climbing
	FRotator RotationAfterClimb;

	//Store the actor that owns the wall surface the climbing trace has hit
	AActor* WallActor;

	//Store most recent location of WallActor (used during ticking to keep track of moving walls/ledges)
	FVector WallActorMostRecentLocation;

	// Store character capsule's original halfheight value before amending it for climb
	float OriginalCapsuleHalfHeight;

	// Store character capsule's original radius value before amending it for climb
	float OriginalCapsuleRadius;
};
