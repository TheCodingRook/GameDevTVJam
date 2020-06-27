// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameDevTVJamStatics.h"
#include "Pickup.generated.h"

/**
 * Base class to implement consumable pickup items in the world
 */

UCLASS()
class GAMEDEVTVJAM_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Pickup")
		UStaticMeshComponent* GetMesh() const;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetMesh(class UStaticMesh* NewMesh);

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool isActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool NewPickupState);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the pickup is collected
	virtual void WasCollected();

	bool bIsActive;


	/** Sound to play when Pickup is collected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	class USoundBase* PickupSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh; // forward decleration here
};