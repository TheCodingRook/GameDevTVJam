// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TimePickupRotating.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimePickupWidget.h"
#include "TimerManager.h"
#include "Materials/MaterialInterface.h"

ATimePickupRotating::ATimePickupRotating()
{
	WidgetArray.AddUnique(Widget);
	ExtraTimeArray.Add(GOLD_TIME);
	MaterialsArray.Add(Gold_Material);
	ActiveWidget = Widget;

	// Set up the new WidgetComponents
	Widget2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeWidget2"));
	Widget2->SetupAttachment(PickupMesh);

	Widget2->SetVisibility(false);
	WidgetArray.AddUnique(Widget2);
	ExtraTimeArray.Add(SILVER_TIME);
	MaterialsArray.Add(Silver_Material);
	
	Widget3 = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeWidget3"));
	Widget3->SetupAttachment(PickupMesh);
	Widget3->SetVisibility(false);
	WidgetArray.AddUnique(Widget3);
	ExtraTimeArray.Add(COPPER_TIME);
	MaterialsArray.Add(Copper_Material);
	
	Widget4 = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeWidget4"));
	Widget4->SetupAttachment(PickupMesh);
	Widget4->SetVisibility(false);
	WidgetArray.AddUnique(Widget4);
	ExtraTimeArray.Add(NICKEL_TIME);
	MaterialsArray.Add(Nickel_Material);
	
	static ConstructorHelpers::FClassFinder<UUserWidget>DefaultTimeWidgetClass(TEXT("/Game/UI/WidgetBlueprints/WBP_TimePickup"));
	if (DefaultTimeWidgetClass.Class != nullptr)
	{
		Widget2->SetWidgetClass(DefaultTimeWidgetClass.Class);
		Widget3->SetWidgetClass(DefaultTimeWidgetClass.Class);
		Widget4->SetWidgetClass(DefaultTimeWidgetClass.Class);
	}

	StartingRotation = GetActorRotation();
	ActiveWidgetIterator = 0;
}

void ATimePickupRotating::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	if (bIsActive && OtherActor == Cast<AGameDevTVJamCharacter>(UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)))
	{
		GetWorldTimerManager().ClearTimer(PyramidRotator);

		PlayTimeWidgetAnimationRotating();
		Super::NotifyActorBeginOverlap(OtherActor);
	}


}

void ATimePickupRotating::WasCollected()
{
	Super::WasCollected();
}

void ATimePickupRotating::BeginPlay()
{
	Super::BeginPlay();
	
	Widget2->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
	Widget3->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
	Widget4->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());

	// Add a looping timer to rotate the pyramid at fixed intervals
	GetWorldTimerManager().SetTimer(PyramidRotator, this, &ATimePickupRotating::RotatePyramid, 3.0f, true, -1.f);
}

void ATimePickupRotating::UpdatePyramid()
{
	ActiveWidget->SetVisibility(false);
	ActiveWidgetIterator++;
	ActiveWidgetIterator = (ActiveWidgetIterator % 4);
	
	ActiveWidget = WidgetArray[ActiveWidgetIterator];
	ActiveWidget->SetVisibility(true);
	ExtraTime = ExtraTimeArray[ActiveWidgetIterator];
	PickupMesh->SetMaterial(0, MaterialsArray[ActiveWidgetIterator]);

	Cast<UTimePickupWidget>(ActiveWidget->GetUserWidgetObject())->UpdateTimeText(ExtraTime);
	//StartingRotation = GetActorRotation();
}
