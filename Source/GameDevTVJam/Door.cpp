// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "Door.h"
#include "PuzzleComponent.h"
#include "PuzzleElementComponent.h"

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &ADoor::AttemptOperateDoor);
		PuzzleElement->OnPuzzleElementDeactivated.AddDynamic(this, &ADoor::AttemptOperateDoor);
	}

	// This is to initiate any triggering actions that happen offscreen (e.g. if I have placed
	// a barrel suspended in mid-air which is supposed to fall on a platform trigger for player
	// to find in that position later in the game.
	AttemptOperateDoor();
}

void ADoor::AttemptOperateDoor()
{
	switch (Puzzle->GetLogicGateType())
	{
	case LogicGateType::OR:
		if (ORTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	case LogicGateType::AND:
		if (ANDTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	case LogicGateType::XOR:
		if (XORTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	case LogicGateType::NOR:
		if (NORTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	case LogicGateType::XNOR:
		if (XNORTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	case LogicGateType::NAND:
		if (NANDTest())
		{
			if (!bIsOpen)
			{
				bIsOpen = true;
				OnTriggered();
				OpenDoor();
			}
		}
		else
		{
			if (bIsOpen)
			{
				bIsOpen = false;
				OnTriggered();
				CloseDoor();
			}
		}
		break;
	default:
		break;
	}
}
