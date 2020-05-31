// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameDevTVJamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GrabbingAbility.h"
#include "ClimbingAbility.h"
#include "InteractionComponentBase.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGameDevTVJamCharacter::AGameDevTVJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create the custom physics handle component for grabbing objects
	Grabber = CreateDefaultSubobject<UGrabbingAbility>(TEXT("Grabber"));

	// Create the custom climbing ability component to enable climbing
	ClimbingAbility = CreateDefaultSubobject<UClimbingAbility>(TEXT("Climbing Ability"));

}

void AGameDevTVJamCharacter::SetCanClimb(bool NewClimbSetting)
{
	bCanClimb = NewClimbSetting;
}

void AGameDevTVJamCharacter::SetIsClimbing(bool NewClimbingState)
{
	bIsClimbing = NewClimbingState;
}

void AGameDevTVJamCharacter::SetIsClimbingLedge(bool NewClimbingLedgeState)
{
	if (NewClimbingLedgeState)
	{
		bIsClimbing = false;
	}
	bIsClimbingLedge = NewClimbingLedgeState;
	
}

void AGameDevTVJamCharacter::SetIsDroppingFromLedge(bool NewDroppingFromLedgeState)
{
	bIsDroppingFromLedge = NewDroppingFromLedgeState;
}

void AGameDevTVJamCharacter::SetWasMeshAdjusted(bool NewMeshAdjustedFlag)
{
	bWasMeshAdjusted = NewMeshAdjustedFlag;
}

void AGameDevTVJamCharacter::SetIsDead(bool DeathStatus)
{
	bIsDead = DeathStatus;
}

void AGameDevTVJamCharacter::SetEncumbered(bool NewState)
{
	bIsEncumbered = NewState;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGameDevTVJamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGameDevTVJamCharacter::AttemptJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGameDevTVJamCharacter::MoveRight);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AGameDevTVJamCharacter::PerformCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AGameDevTVJamCharacter::PerformUnCrouch);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGameDevTVJamCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AGameDevTVJamCharacter::StopInteracting);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGameDevTVJamCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGameDevTVJamCharacter::TouchStopped);
}

void AGameDevTVJamCharacter::AddKeyToInventory(AActor* KeyToAdd)
{
	InventoryKeyList.AddUnique(KeyToAdd);
}

void AGameDevTVJamCharacter::RemoveKeyFromInventory(AActor* KeyToRemove)
{
	InventoryKeyList.RemoveSingleSwap(KeyToRemove);
}

void AGameDevTVJamCharacter::SetInventoryKeyList(TArray<AActor*> NewList)
{
	InventoryKeyList = NewList;
}

void AGameDevTVJamCharacter::RemoveKeyFromInventory_alt()
{
	if (NumberOfKeys > 0)
	{
		NumberOfKeys--;
	}
}

void AGameDevTVJamCharacter::AttemptJump()
{

	if (bIsClimbing)
	{
		bIsClimbing = false;
		bIsClimbingLedge = true;
	}
	else if (!bIsEncumbered)
	{
		if (JumpSound && !GetMovementComponent()->IsFalling())
		{
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
		}
		Jump();
	}
}

void AGameDevTVJamCharacter::MoveRight(float Value)
{
	if (!bIsClimbing)
	{
		// add movement in that direction
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}
}

void AGameDevTVJamCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	if (bIsClimbing)
	{
		bIsClimbing = false;
		bIsClimbingLedge = true;
	}
	else if (!bIsEncumbered)
	{
		Jump();
	}
}

void AGameDevTVJamCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AGameDevTVJamCharacter::PerformCrouch()
{
	if (!bIsEncumbered && !GetMovementComponent()->IsFalling())
	{
		if (bIsClimbing)
		{
			// Let the player fall from the hanging position
			bIsDroppingFromLedge = true;
			ClimbingAbility->FinishClimbing();
		}
		else
		{
			// Use ACharacter's interface
			Crouch();
		}
	}
}

void AGameDevTVJamCharacter::PerformUnCrouch()
{
	// Use ACharacter's interface
	UnCrouch();
}

void AGameDevTVJamCharacter::Interact()
{
	if (!bIsClimbing)
	{
		if (UInteractionComponentBase* InteractionToExecute = Cast<UMyGameInstance>(GetGameInstance())->GetLatestInteractionCommand())
		{
			InteractionToExecute->ExecuteInteraction(this);
		}
	}
}

void AGameDevTVJamCharacter::StopInteracting()
{
	if (UInteractionComponentBase* InteractionToExecute = Cast<UMyGameInstance>(GetGameInstance())->GetLatestInteractionCommand())
	{
		InteractionToExecute->StopInteraction(this);
	}
}
