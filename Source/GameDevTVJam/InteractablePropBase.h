// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractablePropBase.generated.h"

// Forward declerations
class UStaticMeshComponent;

/*
 * Custom class to implement props in the world the player can interact with (i.e. grab etc.)
 */
UCLASS()
class GAMEDEVTVJAM_API AInteractablePropBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablePropBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetPropMesh() const {	return PropMesh; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PropMesh;
};
