// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "SpikeTrap.h"
#include "PuzzleComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		if (bIsDeathFromAboveTrap)
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &ASpikeTrap::DeathFromAboveTrap);
		}
		else
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &ASpikeTrap::AttemptOperateTrap);
			PuzzleElement->OnPuzzleElementDeactivated.AddDynamic(this, &ASpikeTrap::AttemptOperateTrap);
		}
	}

	OnActorBeginOverlap.AddDynamic(this, &ASpikeTrap::NotifySpikeTrapBeginOverlap);

	// This is to initiate any triggering actions that happen offscreen (e.g. if I have placed
	// a barrel suspended in mid-air which is supposed to fall on a platform trigger for player
	// to find in that position later in the game.
	if (!bIsDeathFromAboveTrap)
	{
		
		AttemptOperateTrap(EPuzzleElementType::Toggle);
	}
}

void ASpikeTrap::OnTriggered()
{
	if (bIsDeathFromAboveTrap)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathFromAboveSound, GetActorLocation());
	}
	else
	{
		Super::OnTriggered();
	}
}

void ASpikeTrap::NotifySpikeTrapBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	OtherActor->TakeDamage(1.f, FDamageEvent::FDamageEvent(),nullptr,nullptr);
}

void ASpikeTrap::AttemptOperateTrap(EPuzzleElementType PuzzleElementType)
{
	switch (Puzzle->GetLogicGateType())
	{
	case LogicGateType::OR:
		if (ORTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	case LogicGateType::AND:
		if (ANDTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	case LogicGateType::XOR:
		if (XORTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	case LogicGateType::NOR:
		if (NORTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	case LogicGateType::XNOR:
		if (XNORTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	case LogicGateType::NAND:
		if (NANDTest())
		{
			if (!bIsActive)
			{
				bIsActive = true;
				OnTriggered();
				SpringTrap();
			}
		}
		else
		{
			if (bIsActive)
			{
				bIsActive = false;
				OnTriggered();
				ResetTrap();
			}
		}
		break;
	default:
		break;
	}
}

void ASpikeTrap::DeathFromAboveTrap_Implementation(EPuzzleElementType PuzzleElementType)
{
	OnTriggered();
}
