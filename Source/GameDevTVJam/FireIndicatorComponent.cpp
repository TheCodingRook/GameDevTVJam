// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "FireIndicatorComponent.h"

// Sets default values for this component's properties
UFireIndicatorComponent::UFireIndicatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UFireIndicatorComponent::SetFireIndicator(AActor* FireIndicatorToSet)
{
	FireIndicator = FireIndicatorToSet;
}

// Called when the game starts
void UFireIndicatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFireIndicatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

