// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AbilityPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API AAbilityPickup : public APickup
{
	GENERATED_BODY()
        
public:

    AAbilityPickup();

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void InitStarsArray();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void PlayStarsEffect();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void PlayAbilityWidgetAnimation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    class UWidgetComponent* AbilityWidget;

    FTimerHandle StarsTimer;

};
