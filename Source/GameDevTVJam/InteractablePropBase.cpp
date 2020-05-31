// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "InteractablePropBase.h"
#include "InteractionComponentBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AInteractablePropBase::AInteractablePropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the mesh for this prop
	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Prop Mesh"));
	SetRootComponent(PropMesh);

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>("Interaction Trigger");
	InteractionTrigger->SetSphereRadius(100.f);
	InteractionTrigger->SetupAttachment(PropMesh);
}

void AInteractablePropBase::OnWasInteractedWith_Implementation()
{
	// To be extended in Blueprint
}

void AInteractablePropBase::OnReEnableInteraction_Implementation()
{
	// To be extended in Blueprint
}

// Called when the game starts or when spawned
void AInteractablePropBase::BeginPlay()
{
	Super::BeginPlay();

	if (!InteractionClass)
	{
		UE_LOG(LogTemp, Error, TEXT("You have not specified an interaction component class for: %s"), *GetName())
	}
	else
	{
		InteractionCommand = NewObject<UInteractionComponentBase>(this, InteractionClass);
		if (InteractionCommand)
		{
			InteractionCommand->RegisterComponent();
		}
	}

}

// Called every frame
void AInteractablePropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

