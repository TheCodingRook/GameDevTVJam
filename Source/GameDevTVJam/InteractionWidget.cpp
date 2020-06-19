// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "InteractionWidget.h"
#include "InteractablePropBase.h"
#include "Kismet/GameplayStatics.h"

void UInteractionWidget::SetInteractableProp(AInteractablePropBase* InteractableToSet)
{
	InteractableProp = InteractableToSet;
}

void UInteractionWidget::SetInteractablePropText(FText TextToSet)
{
	InteractablePropText = TextToSet;
}

void UInteractionWidget::SetIsActionAvailable(bool NewAvailability)
{
	bIsActionAvailable = NewAvailability;
}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Adjust location of prompt
	FVector2D PromptScreenLocation;
	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(InteractableProp->GetActorLocation(), PromptScreenLocation))
	{
		SetVisibility(ESlateVisibility::Visible);
		SetPositionInViewport(PromptScreenLocation);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	
}
