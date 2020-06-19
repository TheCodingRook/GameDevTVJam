// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerableActor.generated.h"

/*
 * Custom class to implement actors that have a 'Puzzle' component and get triggered by others
 */

UCLASS()
class GAMEDEVTVJAM_API ATriggerableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerableActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnTriggered();


	class UPuzzleComponent* GetPuzzleComponent() const { return Puzzle; }

protected:
	// Puzzle Component for this triggerable actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Puzzle")
	UPuzzleComponent* Puzzle;

	// Sound to play when actor is triggered (if any)
	UPROPERTY(EditDefaultsOnly, Category = "Puzzle")
	class USoundBase* TriggerSound;

	// Helpful to store starting location if this triggerable actor moves when triggered
	UPROPERTY(BlueprintReadWrite, Category = "Setup setttings")
	FVector StartingLocation;

	// Determines whether to play a trigger sound the first time
	// Useful when things are set to trigger offscreen when game starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup settings")
	bool bMuteFirstSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//////////////////////////////////////////////
	/* Logic tests *//////////////////////////////
	
	bool ORTest();
	bool ANDTest();
	bool XORTest();
	bool NANDTest();
	bool NORTest();
	bool XNORTest();

	/* End logic tests*//////////////////////////
	/////////////////////////////////////////////
};
