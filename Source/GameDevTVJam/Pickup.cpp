// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "Pickup.h"
#include "Engine/StaticMesh.h"
#include "GameDevTVJamCharacter.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	// All pickups start active
	bIsActive = true;

	// Set up the sound component for pickups
	PickupSound = CreateDefaultSubobject<USoundBase>(TEXT("PickupSound"));
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* APickup::GetMesh() const
{
	return PickupMesh;
}

void APickup::SetMesh(UStaticMesh* NewMesh)
{
	PickupMesh->SetStaticMesh(NewMesh);
}

void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bIsActive && OtherActor == Cast<AGameDevTVJamCharacter>(UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)))
	{
		bIsActive = false;
		WasCollected();
	}
}

void APickup::WasCollected()
{
	// Deactive this pickup, though may be unnecessary if I destroy immediately afterwards
	bIsActive = false;
	
	// Destroy the pickup
	Destroy();
}

