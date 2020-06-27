// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "AbilityPickup.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

AAbilityPickup::AAbilityPickup()
{
	// Set up the WidgetComponent
	AbilityWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("AbilityWidget"));
	AbilityWidget->SetupAttachment(PickupMesh);
	AbilityWidget->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget>DefaultTimeWidgetClass(TEXT("/Game/UI/WidgetBlueprints/WBP_AbilityPickup"));
	if (DefaultTimeWidgetClass.Class != nullptr)
	{
		AbilityWidget->SetWidgetClass(DefaultTimeWidgetClass.Class);
	}
}

void AAbilityPickup::BeginPlay()
{
	Super::BeginPlay();
	InitStarsArray();
	
	GetWorldTimerManager().SetTimer(StarsTimer, this, &AAbilityPickup::PlayStarsEffect, 0.07f, true, -1.f);

}

void AAbilityPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (bIsActive && OtherActor == Cast<AGameDevTVJamCharacter>(UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)))
	{
		GetWorldTimerManager().ClearTimer(StarsTimer);
		AbilityWidget->SetVisibility(true);
		Cast<AGameDevTVJamCharacter>(OtherActor)->SetCanClimb(true);
		PlayAbilityWidgetAnimation();
		Super::NotifyActorBeginOverlap(OtherActor);
	}
}
