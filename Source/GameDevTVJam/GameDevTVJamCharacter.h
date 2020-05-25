// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameDevTVJamCharacter.generated.h"

UCLASS(config=Game)
class AGameDevTVJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddKeyToInventory(AActor* KeyToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveKeyFromInventory(AActor* KeyToRemove);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<AActor*> GetInventoryKeys() const { return InventoryKeyList; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryKeyList(TArray<AActor*> NewList);

	/* Alternative implementation for keys
	 *
	 */

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddKeyToInventory_alt() { NumberOfKeys++; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveKeyFromInventory_alt();

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int GetNumberOfKeys() const { return NumberOfKeys; }

protected:

	class UGrabbingAbility* Grabber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	class UClimbingAbility* ClimbingAbility;

	/** A simple array to hold keys the player collects */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AActor*> InventoryKeyList;

	/** Alternative implementation: an integer to hold the number of keys the player collects */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumberOfKeys;

	/** Custom call for jump */
	void AttemptJump();

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Called for starting crouching */
	void PerformCrouch();

	/** Called for ending crouching */
	void PerformUnCrouch();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Called for interacting with an interactable */
	void Interact();

	/** Called for stopping interaction with an interactable */
	void StopInteracting();

public:
	AGameDevTVJamCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Returns encumbered state
	UFUNCTION(BlueprintPure)
	bool IsEncumbered() const { return bIsEncumbered; }

	// Sets the encumbered state of the character
	void SetEncumbered(bool NewState);

	// Sets the climbing ability
	UFUNCTION(BlueprintCallable)
	void SetCanClimb(bool NewClimbSetting);

	// Returns whether character is climbing
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool IsClimbing() const { return bIsClimbing; }

	// Sets the climbing boolean
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetIsClimbing(bool NewClimbingState);

	// Returns whether character is climbing on top of ledge
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool IsClimbingLedge() const { return bIsClimbingLedge; }

	// Sets the climbingLedge boolean
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetIsClimbingLedge(bool NewClimbingLedgeState);

	// Returns whether character is climbing on top of ledge
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool IsDroppingFromLedge() const { return bIsDroppingFromLedge; }

	// Sets the climbingLedge boolean
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetIsDroppingFromLedge(bool NewDroppingFromLedgeState);


	// Gets Climbing Ability component
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	UClimbingAbility* GetClimbingAbility() const { return ClimbingAbility; }

	UFUNCTION(BlueprintPure, Category = "ClimbingAbility")
	bool WasMeshAdjusted() const { return bWasMeshAdjusted; }

	UFUNCTION(BlueprintCallable, Category = "ClimbingAbility")
	void SetWasMeshAdjusted(bool NewMeshAdjustedFlag);

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsDead(bool DeathStatus);

protected:
	// Bool to let the animation blueprint know character is hanging
	// WEIRD BUG! DON'T REMOVE THIS BOOL, THE ANIMATION STOPS WORKING IF YOU DO!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bIsHanging;

	// Bool to let the animation blueprint know character is climbing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bIsClimbing;

	// Bool to let the animation blueprint know character is hanging
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bIsClimbingLedge;

	// Bool to let the animation blueprint know character is dropping from a ledge
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bIsDroppingFromLedge;

	// Bool to keep track if Mesh needs re-adjusting if death occurs in the midst of climbing 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bWasMeshAdjusted;

	// Bool to keep track if player is alive
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	bool bIsDead;

	// Bool to store the player's current climbing ability status (enabled or disabled)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing Ability") // Leave EditAnywhere for debugging purposes only!
	bool bCanClimb;

private:
	// Bool to store the player's current carrying status
	bool bIsEncumbered;
};
