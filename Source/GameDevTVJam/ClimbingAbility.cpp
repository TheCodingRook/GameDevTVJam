// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "ClimbingAbility.h"
#include "GameDevTVJamCharacter.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UClimbingAbility::UClimbingAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UClimbingAbility::Climb()
{
	OwnerCharacter = Cast<AGameDevTVJamCharacter>(GetOwner());

	FHitResult WallHitResult;
	FVector WallTraceStart = FVector(OwnerCharacter->ActorToWorld().GetLocation() + FVector(0.f, 0.f, WallTraceZOffset));

	FVector WallTraceEnd = WallTraceStart + (OwnerCharacter->GetActorForwardVector() * ClimbProximity);

	FCollisionQueryParams WallClimbQueryParams;
	WallClimbQueryParams.AddIgnoredActor(OwnerCharacter);

	//DrawDebugLine(GetWorld(), WallTraceStart, WallTraceEnd, FColor::Red, false , 1.f,(uint8)'\000', 5.f);

	FVector WallLocation;
	FVector WallNormal = WallHitResult.Normal;

	bool FoundVerticalWall = GetWorld()->SweepSingleByChannel(
		WallHitResult,
		WallTraceStart,
		WallTraceEnd,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(ClimbDetectRadius),
		WallClimbQueryParams
	);

	if (FoundVerticalWall)
	{
		//Get a reference to the actor that owns the hitresult
		WallActor = WallHitResult.GetComponent()->GetOwner();
		WallActorMostRecentLocation = WallActor->GetActorLocation();

		WallLocation.X = WallHitResult.Location.X;
		WallLocation.Z = WallHitResult.Location.Z;

		// The Y coordinate is a special case: depending on whether we are facing left or right
		if (OwnerCharacter->GetActorForwardVector().Y < 0)
		{
			WallLocation.Y = WallHitResult.Location.Y - ClimbDetectRadius;
		}
		else
		{
			WallLocation.Y = WallHitResult.Location.Y + ClimbDetectRadius;
		}


		//UE_LOG(LogTemp, Warning, TEXT("Rotation of actor was: %s"), *OwnerCharacter->GetActorForwardVector().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Detected ledge at: %s!"), *WallHitResult.Location.ToString())
		
		//DrawDebugSphere(GetWorld(), WallLocation, ClimbDetectRadius / 2, 16, FColor::Green, false, 1, 5.f);
	}
	else
	{
		//DrawDebugSphere(GetWorld(), WallTraceEnd, ClimbDetectRadius, 16, FColor::Green, false, 1, 5.f);
	}

	// SECOND HORIZONTAL TRACER TO DETECT WALL GAPS ABOVE

	FHitResult GapHitResult;
	FVector GapTraceStart = FVector(OwnerCharacter->ActorToWorld().GetLocation() + FVector(0.f, 0.f, VerticalOffset)); // Adjustment to start higher than the center of player
	FVector GapTraceEnd = GapTraceStart + (OwnerCharacter->GetActorForwardVector() * (ClimbDetectRadius + GapTracerOffset));

	FCollisionQueryParams GapQueryParams;
	GapQueryParams.AddIgnoredActor(OwnerCharacter);

	//DrawDebugLine(GetWorld(), GapTraceStart, GapTraceEnd, FColor::Cyan, false, 1.f, (uint8)'\000', 5.f);

	bool NoGapFound = GetWorld()->SweepSingleByChannel(
		GapHitResult,
		GapTraceStart,
		GapTraceEnd,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(ClimbDetectRadius),
		GapQueryParams
	);

	if (NoGapFound)
	{
		FVector NoGapLocation;

		NoGapLocation.X = GapHitResult.Location.X;
		NoGapLocation.Z = GapHitResult.Location.Z;

		// The Y coordinate is a special case: depending on whether we are facing left or right
		if (OwnerCharacter->GetActorForwardVector().Y < 0)
		{
			NoGapLocation.Y = GapHitResult.Location.Y - ClimbDetectRadius;
		}
		else
		{
			NoGapLocation.Y = GapHitResult.Location.Y + ClimbDetectRadius;
		}
		//DrawDebugSphere(GetWorld(), NoGapLocation, ClimbDetectRadius / 2, 16, FColor::Black, false, 1, 5.f);
	}
	else
	{
		//DrawDebugSphere(GetWorld(), GapTraceEnd, ClimbDetectRadius, 16, FColor::Black, false, 1, 5.f);
	}

	//* Now detect the flat horizontal surface (i.e. top) of detected wall */

	FHitResult FlatSurfaceHitResult;
	FVector FlatSurfaceTraceStart = GapTraceEnd;
	FVector FlatSurfaceTraceEnd = FlatSurfaceTraceStart - (OwnerCharacter->GetActorUpVector() * VerticalOffset);

	//DrawDebugLine(GetWorld(), FlatSurfaceTraceStart, FlatSurfaceTraceEnd, FColor::Yellow, false, 1.f, (uint8)'\000', 5.f);
	

	FCollisionQueryParams FlatSurfaceClimbQueryParams;
	FlatSurfaceClimbQueryParams.AddIgnoredActor(OwnerCharacter);

	FVector LedgeLocation;

	bool FoundFlatSurface = GetWorld()->SweepSingleByChannel(
		FlatSurfaceHitResult,
		FlatSurfaceTraceStart,
		FlatSurfaceTraceEnd,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(ClimbDetectRadius),
		FlatSurfaceClimbQueryParams
	);

	if (FoundFlatSurface)
	{

		// Store the location of the hit result: this is where the player gets teleported at the end
		//LocationAfterClimb = FlatSurfaceHitResult.Location;

		LedgeLocation.X = WallLocation.X; // either of wall or flat surface would probably be fine here
		LedgeLocation.Y = WallLocation.Y;
		LedgeLocation.Z = FlatSurfaceHitResult.Location.Z - ClimbDetectRadius;

		//DrawDebugSphere(GetWorld(), LedgeLocation, ClimbDetectRadius / 2, 16, FColor::Magenta, false, 1, 5.f);
	}

	else
	{
		//DrawDebugSphere(GetWorld(), FlatSurfaceTraceEnd, ClimbDetectRadius, 16, FColor::Magenta, false, 1, 5.f);
	}


	if (FoundVerticalWall && !NoGapFound && !OwnerCharacter->IsDead())
	{
		// Prevent capsule from droppping to the ground due to gravity
		OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		

		RotationAfterClimb = FRotator(0, 90*FMath::RoundToInt(OwnerCharacter->GetActorForwardVector().Y), 0);
		float DistanceFromLedge =
			LedgeLocation.Z -
			OwnerCharacter->GetMesh()->GetSocketByName(FName("HipsSocket"))->GetSocketLocation(OwnerCharacter->GetMesh()).Z;


		OwnerCharacter->GetMesh()->AddLocalOffset(ManualMeshOffset);
		OwnerCharacter->SetWasMeshAdjusted(true);

		OwnerCharacter->GetCapsuleComponent()->MoveComponent(
			FVector(0, // No adjustment on the X-axis as this is a 2D platformer!
			WallLocation.Y - OwnerCharacter->GetActorLocation().Y - OwnerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius() * FMath::RoundToInt(OwnerCharacter->GetActorForwardVector().Y),
			DistanceFromLedge + ManualZOffsetOverride),
			RotationAfterClimb,
			false
		);

		// Reduce the capsule size and radius, after saving original values
		OriginalCapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		OwnerCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeightOverride);
		OriginalCapsuleRadius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
		OwnerCharacter->GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadiusOverride);

		OwnerCharacter->GetCharacterMovement()->StopMovementImmediately();
		//OwnerCharacter->DisableInput(GetWorld()->GetFirstPlayerController());
		OwnerCharacter->SetIsClimbing(true);
	}
}

void UClimbingAbility::ClimbLedge()
{
	
}

void UClimbingAbility::FinishClimbing()
{
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	// Restore capsule original size

	OwnerCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(OriginalCapsuleHalfHeight);
	OwnerCharacter->GetCapsuleComponent()->SetCapsuleRadius(OriginalCapsuleRadius);
	OwnerCharacter->GetMesh()->AddLocalOffset(-ManualMeshOffset);
	OwnerCharacter->SetWasMeshAdjusted(false);
	OwnerCharacter->SetIsClimbing(false);
	OwnerCharacter->SetIsClimbingLedge(false);

	// The following is to fix a peristent bug where the character - despite being locked along the x-axis, 
	// shifts a bit on X after finishing a climb! The universal positioning on X-axis for EVERYTHING on the map
	// (except the braziers and treasure chests for the most part) is 1200!
	OwnerCharacter->SetActorLocation(FVector(1200, OwnerCharacter->GetActorLocation().Y, OwnerCharacter->GetActorLocation().Z));
	
	//OwnerCharacter->EnableInput(GetWorld()->GetFirstPlayerController());
	//OwnerCharacter->GetMesh()->DetachFromParent();

	//OwnerCharacter->GetCapsuleComponent()->MoveComponent(
		//LocationAfterClimb - OwnerCharacter->GetCapsuleComponent()->GetComponentLocation() + FVector(0.f, 0.f, OwnerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()),
		//RotationAfterClimb,
		//false
//	);
	
	//OwnerCharacter->SetActorLocation(LocationAfterClimb + FVector(0.f, 0.f, OwnerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	

}

// Called when the game starts
void UClimbingAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClimbingAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	OwnerCharacter = Cast<AGameDevTVJamCharacter>(GetOwner());
	
	if ((OwnerCharacter->IsClimbing() || OwnerCharacter->IsClimbingLedge()) && !OwnerCharacter->IsDead())
	{
		
		float DeltaY = WallActor->GetActorLocation().Y - WallActorMostRecentLocation.Y;
		float DeltaZ = WallActor->GetActorLocation().Z - WallActorMostRecentLocation.Z;

		//UE_LOG(LogTemp, Warning, TEXT("Delta Y is: %f"), DeltaY)
		//UE_LOG(LogTemp, Warning, TEXT("Delta Z is: %f"), DeltaZ)

		// Update the character capsule's location with the location of the WallActor
		OwnerCharacter->GetCapsuleComponent()->MoveComponent(
			FVector(0,
			DeltaY,
			DeltaZ),			
			RotationAfterClimb,
			false
		);

		//Update the LocationAfterClimb 
		//LocationAfterClimb = LocationAfterClimb + FVector(0.f, DeltaY, DeltaZ);

		WallActorMostRecentLocation = WallActor->GetActorLocation();
	}
}

