// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TriggerActor.h"
#include "PuzzleElementComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PuzzleElement = CreateDefaultSubobject<UPuzzleElementComponent>("Puzzle Element");

}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartingLocation = GetActorLocation();
}

// Only valid for On/Off states, so make sure it is only applied for these two
void ATriggerActor::ToggleState()
{
	if (PuzzleElement->GetTriggerState() == ETriggerState::Off)
	{
		PuzzleElement->SetTriggerState(ETriggerState::On);
	}
	else
	{
		PuzzleElement->SetTriggerState(ETriggerState::Off);
	}
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerActor::OnTriggerActivated()
{
	if (TriggerSound && !bMuteFirstSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, TriggerSound, GetActorLocation());
		bMuteFirstSound = false;
	}

	switch (PuzzleElement->GetPuzzleElementType())
	{

	case EPuzzleElementType::NOSwitch:
	case EPuzzleElementType::Toggle:
		ToggleState();
		// Translate the ETriggerState to an Activated/Deactivated notify.
		// Remember Off is defined first in the enumeration so it's zero (0).
		if ((int)PuzzleElement->GetTriggerState() * 1)
		{
			PuzzleElement->SetElementTriggeredFlag(true);
			PuzzleElement->OnPuzzleElementActivated.Broadcast(PuzzleElement->GetPuzzleElementType());
			PuzzleElement->OnPuzzleElementTriggered.Broadcast(PuzzleElement->GetPuzzleElementType());
		}
		else
		{
			PuzzleElement->SetElementTriggeredFlag(false);
			PuzzleElement->OnPuzzleElementDeactivated.Broadcast(PuzzleElement->GetPuzzleElementType());
			PuzzleElement->OnPuzzleElementUnTriggered.Broadcast(PuzzleElement->GetPuzzleElementType());
		}
		break;
	case EPuzzleElementType::NOSwitch_Rotator:
	case EPuzzleElementType::Toggle_Rotator:
		// Rotators are always triggered true/activated
		PuzzleElement->SetElementTriggeredFlag(true);
		PuzzleElement->OnPuzzleElementActivated.Broadcast(PuzzleElement->GetPuzzleElementType());
		break;
	default:
		break;
	}
}

