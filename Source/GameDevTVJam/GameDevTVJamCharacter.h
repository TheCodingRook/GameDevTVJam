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

protected:

	class UGrabbingAbility* Grabber;
	class UClimbingAbility* ClimbingAbility;

	/** A simple array to hold keys the player collects */
	TArray<AActor*> InventoryKeyList;

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

	/** Called for grabbing */
	void Grab();

	/** Called for ending grabbing */
	void Drop();

	/** Called for interacting with an interactable */
	void Interact();

	/** Called for stopping interaction with an interactable */
	void StopInteracting();

	/** Called for climbing */
	void Climb ();

	/** Called by the Animation Blueprint to finalize the climbing process */
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void FinishClimbing();

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

	// Returns whether character is hanging
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool IsHanging() const { return bIsHanging; }

	// Sets the hanging boolean
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetIsHanging(bool NewHangingState);

	// Returns whether character is climbing
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool IsClimbing() const { return bIsClimbing; }

	// Sets the climbing boolean
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetIsClimbing(bool NewClimbingState);

	// Gets Climbing Ability component
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	UClimbingAbility* GetClimbingAbility() const { return ClimbingAbility; }


protected:
	// Bool to let the animation blueprint know character is hanging
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
		bool bIsHanging;

	// Bool to let the animation blueprint know character is climbing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Climbing Ability")
	bool bIsClimbing;

private:
	// Bool to store the player's current carrying status
	bool bIsEncumbered;

	// Bool to store the player's current climbing ability status (enabled or disabled)
	UPROPERTY(EditAnywhere, Category = "Climbing Ability") // Leave EditAnywhere for debugging purposes only!
	bool bCanClimb;

};
