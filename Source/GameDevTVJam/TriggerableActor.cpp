// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TriggerableActor.h"
#include "PuzzleComponent.h"
#include "PuzzleElementComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerableActor::ATriggerableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Puzzle = CreateDefaultSubobject<UPuzzleComponent>(FName("Puzzle"));

}

// Called when the game starts or when spawned
void ATriggerableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerableActor::OnTriggered()
{
	if (TriggerSound && !bMuteFirstSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, TriggerSound, GetActorLocation());
		bMuteFirstSound = false;
	}
}

bool ATriggerableActor::ORTest()
{
	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		if (PuzzleElement->IsTriggered())
		{
			return true;
		}
	}
	return false;
}

bool ATriggerableActor::ANDTest()
{
	return Puzzle->AreAllPuzzleElementsActive();
}

bool ATriggerableActor::XORTest()
{
	// Test is true if only one, and only one, puzzle element is triggered
	int TriggerCount = 0;

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		if (PuzzleElement->IsTriggered())
		{
			TriggerCount++;
		}
	}
	if (TriggerCount == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ATriggerableActor::NANDTest()
{
	return !ANDTest();
}

bool ATriggerableActor::NORTest()
{
	return !ORTest();
}

bool ATriggerableActor::XNORTest()
{
	// Test is true if either all or none of puzzle elements are triggered (also known as 'equivalence test')
	return (NORTest() || ANDTest());
}

