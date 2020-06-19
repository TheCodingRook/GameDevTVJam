// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "SpikeTrap_Temp.h"
#include "ActorListComponent.h"
#include "PuzzleComponent.h"

// Sets default values
ASpikeTrap_Temp::ASpikeTrap_Temp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpikeTrap_Temp::PostLoad()
{
	Super::PostLoad();

	TInlineComponentArray<UActorListComponent*> ActorListComponent;
	GetComponents(ActorListComponent);

	TInlineComponentArray<UPuzzleComponent*> PuzzleComponent;
	GetComponents(PuzzleComponent);

	PuzzleComponent[0]->SetActorsList(ActorListComponent[0]->ActorList);

}

// Called when the game starts or when spawned
void ASpikeTrap_Temp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeTrap_Temp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

