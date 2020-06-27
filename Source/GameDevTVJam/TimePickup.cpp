// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "TimePickup.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMesh.h"
#include "TimePickupWidget.h"
#include "TimerManager.h"


//float ATimePickup::GOLD_TIME = 10.f;
//float ATimePickup::SILVER_TIME = 5.f;
//float ATimePickup::COPPER_TIME = 1.f;

ATimePickup::ATimePickup()
{
	// Set up the WidgetComponent
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeWidget"));
	Widget->SetupAttachment(PickupMesh);

	static ConstructorHelpers::FClassFinder<UUserWidget>DefaultTimeWidgetClass(TEXT("/Game/UI/WidgetBlueprints/WBP_TimePickup"));
	if (DefaultTimeWidgetClass.Class != nullptr)
	{
		Widget->SetWidgetClass(DefaultTimeWidgetClass.Class);
	}
	
	// Set up the default materials for the time pickups
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_Metal_Gold(TEXT("/Game/Pickups/Materials/M_Metal_Gold"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_Metal_Burnished_Steel(TEXT("/Game/Pickups/Materials/M_Metal_Burnished_Steel"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_Metal_Copper(TEXT("/Game/Pickups/Materials/M_Metal_Copper"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_Metal_Brushed_Nickel(TEXT("/Game/Pickups/Materials/M_Metal_Brushed_Nickel"));

	Gold_Material = M_Metal_Gold.Object;
	Silver_Material = M_Metal_Burnished_Steel.Object;
	Copper_Material = M_Metal_Copper.Object;
	Nickel_Material = M_Metal_Brushed_Nickel.Object;

	// Set up the default meshes for the time pickups
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_NarrowCapsule(TEXT("/Game/Pickups/Meshes/Shape_NarrowCapsule"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sphere(TEXT("/Game/Pickups/Meshes/Shape_Sphere"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_QuadPyramid(TEXT("/Game/Pickups/Meshes/Shape_QuadPyramid"));

	NarrowCapsule_Shape = SM_NarrowCapsule.Object;
	Sphere_Shape = SM_Sphere.Object;
	QuadPyramid_Shape = SM_QuadPyramid.Object;

}

// Called when the game starts or when spawned
void ATimePickup::BeginPlay()
{
	Super::BeginPlay();

	ActiveWidget = Widget;
	Cast<UTimePickupWidget>(ActiveWidget->GetUserWidgetObject())->UpdateTimeText(ExtraTime);

}

void ATimePickup::WasCollected()
{
	// Add time to the player's countdown
	Cast<UMyGameInstance>(GetGameInstance())->AddTime(ExtraTime);
	
	// Hide the mesh...
	PickupMesh->SetVisibility(false);

	// Play pickup sound...
	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());

	// Animate the TimeWidget
	PlayTimeWidgetAnimation();

	// Add a short delay for timewidget animation to play before destroying the actor by calling WasCollected in Super class (Pickup)
	FTimerHandle DelayAfterPickup;
	// Call the helper function to broadcast the notifier after a delay
	GetWorldTimerManager().SetTimer(DelayAfterPickup, this, &ATimePickup::DelaySuperCollected, 1.0f, false, -1.f);
}

void ATimePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (bIsActive && OtherActor == Cast<AGameDevTVJamCharacter>(UGameDevTVJamStatics::GetGameDevTVJamCharacter(this)))
	{
		Super::NotifyActorBeginOverlap(OtherActor);
	}
}

#if WITH_EDITORONLY_DATA
void ATimePickup::PostLoad()
{
	Super::PostLoad();

	//Cast<UTimePickupWidget>(Widget->GetUserWidgetObject())->UpdateTimeText(ExtraTime);
}
#endif

void ATimePickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATimePickup, PickupType))
	{
		switch (PickupType)
		{
		case ETimePickupType::Gold:
			SetMesh(NarrowCapsule_Shape);
			PickupMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
			Widget->SetRelativeScale3D( FVector::OneVector/ PickupMesh->GetRelativeScale3D());
			PickupMesh->SetMaterial(0, Gold_Material);
			ExtraTime = ATimePickup::GOLD_TIME;
			break;
		case ETimePickupType::Silver:
			SetMesh(NarrowCapsule_Shape);
			PickupMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
			Widget->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
			PickupMesh->SetMaterial(0, Silver_Material);
			ExtraTime = ATimePickup::SILVER_TIME;
			break;
		case ETimePickupType::Copper:
			SetMesh(NarrowCapsule_Shape);
			PickupMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
			Widget->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
			PickupMesh->SetMaterial(0, Copper_Material);
			ExtraTime = ATimePickup::COPPER_TIME;
			break;
		case ETimePickupType::Nickel:
			SetMesh(Sphere_Shape);
			PickupMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
			Widget->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
			PickupMesh->SetMaterial(0, Nickel_Material);
			ExtraTime = ATimePickup::NICKEL_TIME;
			break;
		case ETimePickupType::Pyramid: // The starting properties of the rotating pyramid match those of the Gold TimePickup
			SetMesh(QuadPyramid_Shape);
			PickupMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			Widget->SetRelativeScale3D(FVector::OneVector / PickupMesh->GetRelativeScale3D());
			PickupMesh->SetMaterial(0, Gold_Material);
			ExtraTime = ATimePickup::GOLD_TIME;
			break;
		case ETimePickupType::None:
			break;
		}

		// Now update the widget to display the update time content
		Cast<UTimePickupWidget>(Widget->GetUserWidgetObject())->UpdateTimeText(ExtraTime);
	}
}

void ATimePickup::DelaySuperCollected()
{
	Super::WasCollected();
}
