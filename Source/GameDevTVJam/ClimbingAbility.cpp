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
	FVector WallTraceStart = FVector(OwnerCharacter->ActorToWorld().GetLocation());

	FVector WallTraceEnd = WallTraceStart + (OwnerCharacter->GetActorForwardVector() * ClimbProximity);

	FCollisionQueryParams WallClimbQueryParams;
	WallClimbQueryParams.AddIgnoredActor(OwnerCharacter);

	DrawDebugLine(GetWorld(), WallTraceStart, WallTraceEnd, FColor::Red, false , 1.f,(uint8)'\000', 10.f);
	DrawDebugSphere(GetWorld(), WallTraceEnd, ClimbDetectRadius, 16, FColor::Green, false, 1, 5.f);

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
		FVector WallLocation;
		FVector WallNormal = WallHitResult.Normal;
		UE_LOG(LogTemp, Warning, TEXT("Wall Normal was: %s"), *WallNormal.ToString())

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
		

		UE_LOG(LogTemp, Warning, TEXT("Rotation of actor was: %s"), *OwnerCharacter->GetActorForwardVector().ToString());

		UE_LOG(LogTemp, Warning, TEXT("Detected ledge at: %s!"), *WallHitResult.Location.ToString())
		DrawDebugSphere(GetWorld(), WallLocation, 20.f, 16, FColor::Blue, false, 1, 5.f);

		//* Now detect the flat horizontal surface (i.e. top) of detected wall */

		FHitResult FlatSurfaceHitResult;
		
		FVector FlatSurfaceTraceEnd;
			FlatSurfaceTraceEnd.X = OwnerCharacter->ActorToWorld().GetLocation().X,
			FlatSurfaceTraceEnd.Z = OwnerCharacter->ActorToWorld().GetLocation().Z;
		
			// For the Ledge traceline, we want to go just a bit farther out to detect flat surface, but check which direction we are facing
			if (OwnerCharacter->GetActorForwardVector().Y < 0)
			{
				FlatSurfaceTraceEnd.Y = WallLocation.Y - 50.f;
			}
			else
			{
				FlatSurfaceTraceEnd.Y = WallLocation.Y + 50.f;
			}
		

		FVector FlatFaceTraceStart = FlatSurfaceTraceEnd + (OwnerCharacter->GetActorUpVector() * VerticalOffset);
		DrawDebugLine(GetWorld(), FlatFaceTraceStart, FlatSurfaceTraceEnd, FColor::Yellow, false, 1.f, (uint8)'\000', 10.f);
		DrawDebugSphere(GetWorld(), FlatSurfaceTraceEnd, ClimbDetectRadius, 16, FColor::White, false, 1, 5.f);

		FCollisionQueryParams FlatSurfaceClimbQueryParams;
		FlatSurfaceClimbQueryParams.AddIgnoredActor(OwnerCharacter);

		bool FoundFlatSurface = GetWorld()->SweepSingleByChannel(
			FlatSurfaceHitResult,
			FlatFaceTraceStart,
			FlatSurfaceTraceEnd,
			FQuat::Identity,
			ECC_GameTraceChannel1,
			FCollisionShape::MakeSphere(ClimbDetectRadius),
			FlatSurfaceClimbQueryParams
		);

		if (FoundFlatSurface)
		{

			// Store the location of the hit result: this is where the player gets teleported at the end
			LocationAfterClimb = FlatSurfaceHitResult.Location;



			// Calculate ledge's location
			FVector LedgeLocation;

			LedgeLocation.X = WallHitResult.Location.X; // either of wall or flat surface would probably be fine here
			LedgeLocation.Y = WallHitResult.Location.Y;
			LedgeLocation.Z = FlatSurfaceHitResult.Location.Z - ClimbDetectRadius;

			DrawDebugSphere(GetWorld(), LedgeLocation, 20.f, 16, FColor::Orange, false, 1, 5.f);


			// Calculate distance (Z-axis only?) between climb-able ledge and "ClimbSocket" 

			float DistanceFromLedge =
				LedgeLocation.Z -
				OwnerCharacter->GetMesh()->GetSocketByName(FName("HipsSocket"))->GetSocketLocation(OwnerCharacter->GetMesh()).Z -100.f;// Adjustment to work with animation
			

			UE_LOG(LogTemp, Warning, TEXT("Vertical distance from ledge: %f"), DistanceFromLedge)

			// Probably need to check if we can reach the ledge when wall and flat surface on top were detected

			// Prevent capsule from droppping to the ground due to gravity
			OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

			RotationAfterClimb = FRotator(0, -90 * FMath::RoundToInt(WallNormal.Y), 0);
			OwnerCharacter->GetCapsuleComponent()->MoveComponent(
				FVector(OwnerCharacter->GetActorLocation().X - WallLocation.X, WallLocation.Y - OwnerCharacter->GetActorLocation().Y + 50.f * FMath::RoundToInt(WallNormal.Y), DistanceFromLedge),
				RotationAfterClimb,
				false
			);
			OwnerCharacter->GetCharacterMovement()->StopMovementImmediately();
			OwnerCharacter->DisableInput(GetWorld()->GetFirstPlayerController());
			
			// Set the member field of character accordingly
			OwnerCharacter->SetIsClimbing(true);
		}

	}

	

}

void UClimbingAbility::FinishClimbing()
{
	OwnerCharacter->SetIsClimbing(false);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	OwnerCharacter->EnableInput(GetWorld()->GetFirstPlayerController());
	//OwnerCharacter->GetMesh()->MoveComponent(FVector(0.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f), false);

	OwnerCharacter->GetCapsuleComponent()->MoveComponent(
		LocationAfterClimb - OwnerCharacter->GetCapsuleComponent()->GetComponentLocation() + FVector(0.f, 0.f, OwnerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()),
		RotationAfterClimb,
		false
	);
	
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

	// ...
	/*
	OwnerCharacter = Cast<AGameDevTVJamCharacter>(GetOwner());
	
	if (OwnerCharacter->IsClimbing())
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
		LocationAfterClimb = LocationAfterClimb + FVector(0.f, DeltaY, DeltaZ);

		WallActorMostRecentLocation = WallActor->GetActorLocation();
	}
	*/
}

