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
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacter::Crouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacter::UnCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AGameDevTVJamCharacter::PerformCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AGameDevTVJamCharacter::PerformUnCrouch);
	PlayerInputComponent->BindAction("Climb", IE_Pressed, this, &AGameDevTVJamCharacter::Climb);
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

void AGameDevTVJamCharacter::AttemptJump()
{
	if (!bIsEncumbered && !bIsClimbing)
	{
		Jump();
	}
}

void AGameDevTVJamCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AGameDevTVJamCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	if (!bIsEncumbered && !bIsClimbing)
	{
		Jump();
	}
}

void AGameDevTVJamCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AGameDevTVJamCharacter::Grab()
{
	Grabber->Grab();
}

void AGameDevTVJamCharacter::Drop()
{
	Grabber->Drop();
}

void AGameDevTVJamCharacter::PerformCrouch()
{
	if (!bIsEncumbered && !GetMovementComponent()->IsFalling())
	{
		// Use ACharacter's interface
		Crouch();
	}
}

void AGameDevTVJamCharacter::PerformUnCrouch()
{
	// Use ACharacter's interface
	UnCrouch();
}

void AGameDevTVJamCharacter::Interact()
{
	if (UInteractionComponentBase* InteractionToExecute = Cast<UMyGameInstance>(GetGameInstance())->GetLatestInteractionCommand())
	{
		InteractionToExecute->ExecuteInteraction(this);
	}
}

void AGameDevTVJamCharacter::StopInteracting()
{
	if (UInteractionComponentBase* InteractionToExecute = Cast<UMyGameInstance>(GetGameInstance())->GetLatestInteractionCommand())
	{
		InteractionToExecute->StopInteraction(this);
	}
}

void AGameDevTVJamCharacter::Climb()
{
	ClimbingAbility->Climb();
}

void AGameDevTVJamCharacter::FinishClimbing()
{
	ClimbingAbility->FinishClimbing();
}