// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "GrabbingAbility.h"
#include "GameDevTVJamCharacter.h"
#include "Engine/World.h"
#include "InteractablePropBase.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

void UGrabbingAbility::Grab()
{
	OwnerCharacter = Cast<AGameDevTVJamCharacter>(GetOwner());
	
	FHitResult HitResult;
	FVector TraceStart = OwnerCharacter->ActorToWorld().GetLocation();
	FVector TraceEnd = TraceStart + (OwnerCharacter->GetActorForwardVector() * GrabDistance);

	FCollisionQueryParams GrabQueryParams;
	GrabQueryParams.AddIgnoredActor(OwnerCharacter);

	 //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false , 1.f,(uint8)'\000', GrabRadius);
	 //DrawDebugSphere(GetWorld(), TraceEnd, GrabRadius, 16, FColor::Green, false, 1, 10.f);


	 bool FoundSomethingToGrab = GetWorld()->SweepSingleByChannel(
		 HitResult,
		 TraceStart,
		 TraceEnd,
		 FQuat::Identity,
		 ECC_PhysicsBody,
		 FCollisionShape::MakeSphere(GrabRadius),
		 GrabQueryParams
	 );

	 if (FoundSomethingToGrab)
	 {
		 if (AInteractablePropBase * InteractableProp = Cast<AInteractablePropBase>(HitResult.GetActor()))
		 {
			// Enable physics so this actor can work with the physics handlecomponent
			 InteractableProp->GetPropMesh()->SetSimulatePhysics(true);
			// Disable collision for now so we can carry the object without crashing into it
			HitResult.GetComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		 
			// Grab from centre of mass so that it is easier to handle.
			GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, HitResult.GetComponent()->GetCenterOfMass());
		 }
	 }
}

void UGrabbingAbility::Drop()
{
	// First make sure we are indeed grabbing something!
	if (GrabbedComponent)
	{
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		//GrabbedComponent->SetSimulatePhysics(false);

		ReleaseComponent();
	}
}

void UGrabbingAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GrabbedComponent)
	{
		// Magic number! small offset to avoid collisions when dropping afterward, TODO: EXPOSE TO BLUEPRINT
		SetTargetLocation(OwnerCharacter->ActorToWorld().GetLocation() + OwnerCharacter->GetActorForwardVector() * (GrabDistance + 40.f));
	}
}
