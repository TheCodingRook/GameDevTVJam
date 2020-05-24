// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "SavePoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our SaveTrigger collision box
	SaveTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Save Point Trigger"));
	SetRootComponent(SaveTrigger);

	// Create our BlockingTrigger collision box
	BlockingTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Blocking Trigger"));
	SetRootComponent(SaveTrigger);

	// Create the SavePoint's mesh (useful when this is a mid-level SavePoint and needs to be visible)
	SavePointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Save Point Mesh"));
	SavePointMesh->SetupAttachment(SaveTrigger);
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
