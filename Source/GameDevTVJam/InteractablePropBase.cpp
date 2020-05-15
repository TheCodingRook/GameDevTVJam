// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "InteractablePropBase.h"

// Sets default values
AInteractablePropBase::AInteractablePropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the mesh for this prop
	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Prop Mesh"));
	PropMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInteractablePropBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractablePropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

