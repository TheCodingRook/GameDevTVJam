// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "Brazier.h"
#include "PuzzleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

ABrazier::ABrazier()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Brazier");
	SetRootComponent(Mesh);

	Fire = CreateDefaultSubobject<UParticleSystemComponent>("Fire");
	Fire->SetupAttachment(Mesh);
	Fire->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	Fire->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	Light = CreateDefaultSubobject<UPointLightComponent>("Light");
	Light->SetupAttachment(Fire);
	Light->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void ABrazier::BeginPlay()
{
	Super::BeginPlay();

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &ABrazier::ToggleFireEvent);
		PuzzleElement->OnPuzzleElementDeactivated.AddDynamic(this, &ABrazier::ToggleFireEvent);
	}
}

void ABrazier::PostLoad()
{
	Super::PostLoad();
	Fire->SetVisibility(bIsLit);
	Light->SetVisibility(bIsLit);
		
}

void ABrazier::ToggleFireEvent(EPuzzleElementType PuzzleElementType)
{
	ToggleFire();
}

void ABrazier::ToggleFire()
{
	Fire->SetVisibility(!bIsLit);
	Light->SetVisibility(!bIsLit);
	bIsLit = !bIsLit;
}
