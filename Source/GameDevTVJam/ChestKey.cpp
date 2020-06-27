// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "ChestKey.h"
#include "GameDevTVJamStatics.h"

void AChestKey::NotifyKeyBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AGameDevTVJamCharacter* PlayerCharacter = Cast<AGameDevTVJamCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddKeyToInventory();
		//GetMesh()->SetVisibility(false);
		//UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		WasCollected();
		UGameDevTVJamStatics::GetGameHUD(this)->UpdateKeysFound(PlayerCharacter->GetNumberOfKeys());
	}
}

void AChestKey::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AChestKey::NotifyKeyBeginOverlap);
}
