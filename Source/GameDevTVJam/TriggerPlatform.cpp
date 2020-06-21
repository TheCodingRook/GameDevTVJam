// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TriggerPlatform.h"
#include "ActivateTriggerPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

ATriggerPlatform::ATriggerPlatform()
{
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>("Collision Volume");
	SetRootComponent(CollisionVolume);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(CollisionVolume);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CeramicTileChecker_Blue (TEXT("/Game/Puzzles/Materials/MI_Ceramic_Tile_Checker_Blue"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CeramicTileChecker_Red (TEXT("/Game/Puzzles/Materials/MI_Ceramic_Tile_Checker_Red"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CeramicTileChecker_Green (TEXT("/Game/Puzzles/Materials/MI_Ceramic_Tile_Checker_Green"));

	Blue_Material = CeramicTileChecker_Blue.Object;
	Red_Material = CeramicTileChecker_Red.Object;
	Green_Material = CeramicTileChecker_Green.Object;
}

UStaticMeshComponent* ATriggerPlatform::GetMesh()
{
	return Mesh;
}

void ATriggerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ATriggerPlatform::NotifyTriggerPlatformBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ATriggerPlatform::NotifyTriggerPlatformEndOverlap);

	//Save the starting relative location of the mesh
	//StartingRelativeLocation = Mesh->GetRelativeLocation();

	// Overwrite starting location instead?
	StartingLocation = Mesh->GetRelativeLocation();
}

void ATriggerPlatform::NotifyTriggerPlatformBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->Implements<UActivateTriggerPlatform>())
	{
		OverlappingActors.AddUnique(OtherActor);
	}

	if (OverlappingActors.Num() == 1)
	{
		//Only one actor overlapping and activating this TriggerPlatform
		OnTriggerActivated();
		PressPlatform();
	}
}

void ATriggerPlatform::NotifyTriggerPlatformEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->Implements<UActivateTriggerPlatform>())
	{
		OverlappingActors.RemoveSingle(OtherActor);
	}

	if (OverlappingActors.Num() == 0)
	{
		if (PuzzleElement->GetPuzzleElementType() == EPuzzleElementType::NOSwitch)
		{
			OnTriggerActivated();
		}

		// This was the last actor activating this trigger, so now depress it
		DepressPlatform();
	}
}