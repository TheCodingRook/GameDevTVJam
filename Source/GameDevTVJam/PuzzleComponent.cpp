// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "PuzzleComponent.h"
#include "PuzzleElementComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

bool UPuzzleComponent::AreAllPuzzleElementsActive()
{
	if (PuzzleElementsList.Num()>0)
	{
		for (UPuzzleElementComponent* PuzzleElement : PuzzleElementsList)
		{
			if (PuzzleElement->GetTriggerState()==ETriggerState::Off)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

// Called when the game starts
void UPuzzleComponent::BeginPlay()
{
	Super::BeginPlay();

	// Populate the PuzzleElements list
	for (AActor* PuzzleElementActor : ActorsList)
	{
		if (UPuzzleElementComponent* PuzzleElementComponentFound = Cast<UPuzzleElementComponent>(PuzzleElementActor->GetComponentByClass(UPuzzleElementComponent::StaticClass())))
		{
			PuzzleElementsList.AddUnique(PuzzleElementComponentFound);
		}
	}

}


// Called every frame
void UPuzzleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
