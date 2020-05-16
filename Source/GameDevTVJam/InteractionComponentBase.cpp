// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "InteractionComponentBase.h"
#include "InteractablePropBase.h"

// Sets default values for this component's properties
UInteractionComponentBase::UInteractionComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	InteractionText = FText::FromString("Interact with").ToUpper();
}

// Called every frame
void UInteractionComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponentBase::ExecuteInteraction(AGameDevTVJamCharacter* Instigator)
{
	if (AInteractablePropBase* OwnerProp = Cast<AInteractablePropBase>(GetOwner()))
	{
		OwnerProp->OnWasInteractedWith();
	}
}

void UInteractionComponentBase::StopInteraction(AGameDevTVJamCharacter* Instigator)
{
	if (AInteractablePropBase* OwnerProp = Cast<AInteractablePropBase>(GetOwner()))
	{
		// end interaction, implement in subclasses
	}
}

// Called when the game starts
void UInteractionComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

