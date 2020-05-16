// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "GrabInteraction.h"
#include "InteractablePropBase.h"
#include "GrabbingAbility.h"
#include "GameDevTVJamCharacter.h"

UGrabInteraction::UGrabInteraction()
{
	InteractionText = FText::FromString("Grab").ToUpper();
}

void UGrabInteraction::ExecuteInteraction(AGameDevTVJamCharacter* Instigator)
{
	Super::ExecuteInteraction(Instigator);

	AInteractablePropBase* PropToGrab = Cast<AInteractablePropBase>(GetOwner());

	// Get the Grabbing ability component via the array returned by GetCompnents()
	TInlineComponentArray<UGrabbingAbility*> GrabComponents;
	Instigator->GetComponents(GrabComponents);

	// We expect this to be the first and only component of its kind!
	GrabComponents.Top()->Grab();
}
