// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireIndicatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEVTVJAM_API UFireIndicatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireIndicatorComponent();


	// Return the Actor (should be BP_Brazier) that this actor is linked to
	UFUNCTION(BlueprintPure, Category = "Fire Indicator")
	AActor* GetFireIndicator() const { return FireIndicator; }

	// Set the Actor (FireIndicator - BP_Brazier) that this actor should be linked to
	UFUNCTION(BlueprintCallable, Category = "Fire Indicator")
	void SetFireIndicator(AActor* FireIndicatorToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Indicator")
	AActor* FireIndicator;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
