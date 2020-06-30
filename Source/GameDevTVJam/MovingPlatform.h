// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleElementComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class GAMEDEVTVJAM_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	class UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Puzzle")
	class UPuzzleComponent* Puzzle;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	FVector StartingLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	FVector LERP_StartingLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	FRotator LERP_StartingRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	FVector DistanceToTravel;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	FVector DistanceTraveled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float SpeedMultiplier;

	UPROPERTY(BlueprintReadWrite, Category = "Movement Settings")
	bool OriginalPlayDirection;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Starts the initial repeating movement of the platform
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void StartMovingPlatform();

	// Attempts to change the way the platform moves
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
		void AttemptChangeMovement(EPuzzleElementType ElementType);
};
