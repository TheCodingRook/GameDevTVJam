// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PushNewInteractionCommand(class UInteractionComponentBase* NewInteraction);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PopInteractionCommand(UInteractionComponentBase* InteractionCommandToRemove);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	UInteractionComponentBase* GetLatestInteractionCommand();

	UFUNCTION(BlueprintPure, Category = "Interaction Commands")
	TArray<UInteractionComponentBase*> GetInteractionCommandStack() const { return InteractionCommandStack; }

private:
	TArray<UInteractionComponentBase*> InteractionCommandStack;
};
