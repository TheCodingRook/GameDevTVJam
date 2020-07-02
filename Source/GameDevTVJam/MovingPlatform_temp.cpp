// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MovingPlatform_temp.h"
#include "ActorListComponent.h"
#include "PuzzleComponent.h"

// Sets default values
AMovingPlatform_temp::AMovingPlatform_temp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ActorListComponent = CreateDefaultSubobject<UActorListComponent>("Actor List");

}

void AMovingPlatform_temp::PostLoad()
{
	Super::PostLoad();

	TInlineComponentArray<UActorListComponent*> ActorListComponent;
	GetComponents(ActorListComponent);

	TInlineComponentArray<UPuzzleComponent*> PuzzleComponent;
	GetComponents(PuzzleComponent);

	//UE_LOG(LogTemp, Warning, TEXT("Found %i ActorListComponents in"), ActorListComponent.Num())

	//ActorListComponent[0]->ActorList = PuzzleComponent[0]->GetActorsList();
}

// Called when the game starts or when spawned
void AMovingPlatform_temp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform_temp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

