// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActor.h"
#include "TriggerPlatform.generated.h"

/**
 * Custom class to implement a trigger platform 
 */
UCLASS()
class GAMEDEVTVJAM_API ATriggerPlatform : public ATriggerActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Platform movement")
		void PressPlatform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Platform movement")
		void DepressPlatform();

	void BeginPlay() override;

protected:
	// How much to press the platform by (vertical movement intended here)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform movement")
	float PlatformZOffset;
};
