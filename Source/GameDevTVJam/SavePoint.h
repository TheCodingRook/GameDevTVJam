// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SavePoint.generated.h"

/**
 * Custom class to implement savepoints during the game
 */

UCLASS()
class GAMEDEVTVJAM_API ASavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavePoint();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Find out if this Level is active
	UFUNCTION(BlueprintPure, Category = "Save Point")
	bool IsActive() const { return bIsActive; }

	// Find out if this a new Level savepoint
	UFUNCTION(BlueprintPure, Category = "Save Point")
	bool IsNewLevel() const { return bIsNewLevel; }

	UFUNCTION()
	void OnSaveTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBlockingTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Is this SavePoint active? (not already reached)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Point")
	bool bIsActive = true;

	// Is this SavePoint the start of a new Level?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Point")
	bool bIsNewLevel;

	// SavePoint's trigger volume 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Point", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SaveTrigger;

	// SavePoint's additional trigger volume that causes the main one to block the player to go back
	// It helps prevent player from activating save point but immediately going backwards and locking themselves out of next level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Point", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BlockingTrigger;

	// SavePoint's pickup-type mesh, for mid-level savepoints (the Player needs to be able to see those SavePoints!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Point", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SavePointMesh;

	// Helper vector to fine tune the location to respawn the location at/near the last save point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
	FVector SpawnVectorOffset;
};
