// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "PainBox.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
APainBox::APainBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("DeathSprite");
	SetRootComponent(SpriteComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("PainBox");
	CollisionComponent->SetupAttachment(SpriteComponent);
}

// Called when the game starts or when spawned
void APainBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APainBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APainBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	OtherActor->TakeDamage(PainBoxDamage, FDamageEvent::FDamageEvent(), nullptr, nullptr);
}

