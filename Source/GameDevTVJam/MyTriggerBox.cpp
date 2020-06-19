// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MyTriggerBox.h"
#include "PuzzleElementComponent.h"

AMyTriggerBox::AMyTriggerBox()
{
	PuzzleElement = CreateDefaultSubobject<UPuzzleElementComponent>("Puzzle Element");
}

void AMyTriggerBox::NotifyTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	PuzzleElement->OnPuzzleElementActivated.Broadcast();
	PuzzleElement->SetElementTriggeredFlag(true);
}

void AMyTriggerBox::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::NotifyTriggerBeginOverlap);
}
