// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "InteractablePropBase.h"
#include "InteractionComponentBase.h"
#include "Components/SphereComponent.h"
#include "InteractionWidget.h"
#include "GameDevTVJamStatics.h"

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

void AInteractablePropBase::OnWasInteractedWith()
{
	if (bIsWidgetNecessary)
	{
		InteractionPrompt->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		InteractionPrompt->RemoveFromParent();
	}
	UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetActorLocation());
}

void AInteractablePropBase::OnReEnableInteraction()
{		
	if (bIsWidgetNecessary)
	{
		// Set the screen location of the interaction prompt widget first and then add to viewport!
		SetPromptScreenLocation();

		InteractionPrompt->SetVisibility(ESlateVisibility::Visible);
	}
}

void AInteractablePropBase::OnPropBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AGameDevTVJamCharacter* PlayerCharacter = Cast<AGameDevTVJamCharacter>(OtherActor);
	if (PlayerCharacter)
	{
	//	if (!InteractionPrompt)
		//{	// Create interaction prompt widget if there isn't one yet
			InteractionPrompt = CreateWidget<UInteractionWidget>(GetWorld(), InteractionPromptClass, FName("Interaction Prompt"));
			InteractionPrompt->SetInteractableProp(this);
			InteractionPrompt->SetInteractablePropText(InteractionCommand->GetInteractionText());

			// Update appearance of the propmt widget
			InteractionPrompt->SetIsActionAvailable(ComboQuery(PlayerCharacter));
			InteractionPrompt->UpdateInteractionPrompt();
			
			if (bIsWidgetNecessary)
			{
				// Set the screen location of the interaction prompt widget first and then add to viewport!
				SetPromptScreenLocation();
				InteractionPrompt->AddToViewport();
			}
	//	}
	/*	else
		{
			UE_LOG(LogTemp, Warning, TEXT("Recycling existing widget..."))
			if (bIsWidgetNecessary)
			{
				// Update appearance of the propmt widget
				InteractionPrompt->SetIsActionAvailable(ComboQuery(PlayerCharacter));
				InteractionPrompt->UpdateInteractionPrompt();

				// Set the screen location of the interaction prompt widget 
				SetPromptScreenLocation();

				// Make widget visible again
				InteractionPrompt->SetVisibility(ESlateVisibility::Visible);
				UE_LOG(LogTemp, Warning, TEXT("Setting %s's prompt visible again"), *GetName())
				UE_LOG(LogTemp, Warning, TEXT("Prompt object name: %s"), *InteractionPrompt->GetName())
			}
		}
	*/
		// Register the interaction command with the Game Instance
		Cast<UMyGameInstance>(GetGameInstance())->PushNewInteractionCommand(InteractionCommand);
	}
}

void AInteractablePropBase::OnPropEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName())
	AGameDevTVJamCharacter* PlayerCharacter = Cast<AGameDevTVJamCharacter>(OtherActor);
	if (PlayerCharacter)
	{
	//	if (InteractionPrompt)
	//	{
	//		if (bIsWidgetNecessary)
	//		{
	//			InteractionPrompt->SetVisibility(ESlateVisibility::Hidden);
				UE_LOG(LogTemp, Warning, TEXT("Just hiding prompt..."))
	//		}
	//		else
	//		{
				InteractionPrompt->RemoveFromParent();
	//		}
	//	}

		// De-register the interaction command with the Game Instance
		Cast<UMyGameInstance>(GetGameInstance())->PopInteractionCommand(InteractionCommand);
	}
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

	OnActorBeginOverlap.AddDynamic(this, &AInteractablePropBase::OnPropBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AInteractablePropBase::OnPropEndOverlap);

}

bool AInteractablePropBase::ComboQuery(AGameDevTVJamCharacter* PlayerCharacter)
{
	return true;
}

void AInteractablePropBase::SetPromptScreenLocation()
{
	FVector2D ScreenLocation;
	UGameDevTVJamStatics::GetGameDevTVJamController(this)->ProjectWorldLocationToScreen(GetActorLocation() + CustomWidgetOffset,ScreenLocation);
	InteractionPrompt->SetPositionInViewport(ScreenLocation);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ScreenLocation.ToString())
	
}

// Called every frame
void AInteractablePropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

