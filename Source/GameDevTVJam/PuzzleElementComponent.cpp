// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "PuzzleElementComponent.h"
#include "TriggerPlatform.h"

// Sets default values for this component's properties
UPuzzleElementComponent::UPuzzleElementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

#if WITH_EDITORONLY_DATA
void UPuzzleElementComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	// Detect if we are changing the PuzzleElementType member field (NOSwitch or Toggle etc.)
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UPuzzleElementComponent, PuzzleElementType))
	{
		if (ATriggerPlatform* TriggerPlatform = Cast<ATriggerPlatform>(GetOwner()))
		{
			if (PuzzleElementType == EPuzzleElementType::NOSwitch)
			{
				TriggerPlatform->GetMesh()->SetMaterial(0, TriggerPlatform->Blue_Material);
			}
			else if (PuzzleElementType == EPuzzleElementType::Toggle)
			{
				TriggerPlatform->GetMesh()->SetMaterial(0, TriggerPlatform->Red_Material);
			}
			else if (PuzzleElementType == EPuzzleElementType::NOSwitch_Rotator || PuzzleElementType == EPuzzleElementType::Toggle_Rotator)
			{
				TriggerPlatform->GetMesh()->SetMaterial(0, TriggerPlatform->Green_Material);
			}
		}
	}
}
#endif

// Called when the game starts
void UPuzzleElementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPuzzleElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPuzzleElementComponent::SetElementTriggeredFlag(bool InFlag)
{
	bIsTriggered = InFlag;
}

void UPuzzleElementComponent::ToggleTrigger()
{
	bIsTriggered = !bIsTriggered;
}

void UPuzzleElementComponent::SetPuzzleElementType(EPuzzleElementType InElementType)
{
	PuzzleElementType = InElementType;
}

void UPuzzleElementComponent::SetTriggerState(ETriggerState InTriggerState)
{
	TriggerState = InTriggerState;
}
