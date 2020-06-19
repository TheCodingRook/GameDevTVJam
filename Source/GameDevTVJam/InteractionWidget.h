// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void UpdateInteractionPrompt();

	void SetInteractableProp(class AInteractablePropBase* InteractableToSet);
	void SetInteractablePropText(FText TextToSet);
	void SetIsActionAvailable(bool NewAvailability);

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Interactable Prop")
	AInteractablePropBase* InteractableProp;

	UPROPERTY(BlueprintReadWrite, Category = "Interactable Prop")
	FText InteractablePropText;
	
	// Bool to determine the appearance of the propmpt based on interaction availability
	UPROPERTY(BlueprintReadWrite, Category = "Interactable Prop")
	bool bIsActionAvailable;

	// How much faded out interaction prompt looks when interaction is unavailable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Prop")
	float UnAvailableRenderOpacity;
};
