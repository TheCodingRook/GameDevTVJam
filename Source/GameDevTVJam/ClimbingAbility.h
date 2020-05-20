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
	float ClimbProximity = 120;

	// Radius of climbing detection sphere when facing forward (i.e. how high up can we detect ledges?)
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Configuration")
	float ClimbDetectRadius = 10.f;

	// Vertical offset for secondary trace to detect ledge height
	UPROPERTY(EditDefaultsOnly, Category = "Climbing Settings")
	float VerticalOffset = 110; 

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
};
