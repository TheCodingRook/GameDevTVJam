// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabbingAbility.generated.h"

/**
 * 
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEDEVTVJAM_API UGrabbingAbility : public UPhysicsHandleComponent
{
	GENERATED_BODY()

public:
	//~ Getter methods

	UFUNCTION(BlueprintPure, Category = "Grab Configuration")
		float GetGrabDistance() const { return GrabDistance; }

	UFUNCTION(BlueprintCallable, Category = "Grab Configuration")
		void Grab();

	UFUNCTION(BlueprintCallable, Category = "Grab Configuration")
		void Drop();

protected:
	//~ Set up some space and distance parameters for the grabbing ability (Remember it is IN CENTIMETERS!)

	// Minimum distance before the player can grab an object
	UPROPERTY(EditAnywhere, Category = "Grab Configuration")
		float GrabDistance = 40.f;

	// Radius of grabbing range when facing forward
	UPROPERTY(EditAnywhere, Category = "Grab Configuration")
		float GrabRadius = 50.f;

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Private member to store the pointer to the player character
	class AGameDevTVJamCharacter* OwnerCharacter;

	// Store the pointer to a prop that was recently dropped so we can reset its physics simulation setting
	AActor* RecentlyDroppedActor;
};
