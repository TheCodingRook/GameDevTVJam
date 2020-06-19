// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameDevTVJamCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerWon);

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

	/** Called for pausing game */
	void PauseGame();

public:
	AGameDevTVJamCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/*~ Delegates for win/lose states*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatchers", meta = (AllowPrivateAccess = true))
	FPlayerDied OnPlayerDied;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatchers", meta = (AllowPrivateAccess = true))
	FPlayerWon OnPlayerWon;


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
	UFUNCTION(BlueprintCallable, Category = "Climbing Ability")
	void SetCanClimb(bool NewClimbSetting);

	// Sets the climbing ability
	UFUNCTION(BlueprintPure, Category = "Climbing Ability")
	bool GetCanClimb() const { return bCanClimb; }

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

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsVictorious() const { return bIsVictorious; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsDead(bool DeathStatus);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsVictorious(bool VictoryStatus);

	UFUNCTION(BlueprintPure, Category = "Inventory")
		TArray<AActor*> GetInventoryKeys() const { return InventoryKeyList; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetInventoryKeyList(TArray<AActor*> NewList);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddKeyToInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void RemoveKeyFromInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetNumberOfKeys( int NewKeyes) { NumberOfKeys = NewKeyes; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
		int GetNumberOfKeys() const { return NumberOfKeys; }

	// Helper function called by GameMode to perform a victory animation when player wins
	void VictoryAnimation();

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
	bool bIsDead = false;

	// Bool to store the player's current climbing ability status (enabled or disabled)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing Ability") // Leave EditAnywhere for debugging purposes only!
	bool bCanClimb;

	// Bool for setting player win state
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	bool bIsVictorious;

	/** Sound to play each time we jump */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* JumpSound;

	/** Sound to play at death */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* DeathSound;

private:
	// Bool to store the player's current carrying status
	bool bIsEncumbered;
};
