// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool isActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool NewPickupState);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		float GetPickupLifeSpan() const { return PickupLifeSpan; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the pickup is collected
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pickup")
		void WasCollected();

	bool bIsActive;

	// How long does the pickup remain active?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float PickupLifeSpan; // TODO: Do I need a setter?

	/** Sound to play when Pickup is collected */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	class USoundBase* PickupSound;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PickupMesh; // forward decleration here
};