// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MovingPlatform.h"
#include "PuzzleComponent.h"
#include "MyTriggerBox.h"
#include "TriggerActor.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	SetRootComponent(Platform);

	Puzzle = CreateDefaultSubobject<UPuzzleComponent>("Puzzle");
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* LinkedActor : Puzzle->GetActorsList())
	{
		// Deal with linked actors that spawn a PuzzleElement dynamically that this MovingPlatform is to be linked with
		if (LinkedActor->ActorHasTag(FName("SpawnsPuzzleElement")))
		{
			// deal with linking spawned puzzle elements at runtime
		}
	}

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		// Distinguish between trigger boxes and TriggerPlatforms
		if (AMyTriggerBox* TriggerBox = Cast<AMyTriggerBox>(PuzzleElement->GetOwner()))
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &AMovingPlatform::StartMovingPlatform);
		}
		else if (ATriggerActor* TriggerActor = Cast<ATriggerActor>(PuzzleElement->GetOwner()))
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &AMovingPlatform::AttemptChangeMovement);
			PuzzleElement->OnPuzzleElementDeactivated.AddDynamic(this, &AMovingPlatform::AttemptChangeMovement);
		}
	}

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

