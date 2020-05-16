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

	UFUNCTION(BlueprintPure, Category = "Interaction Trigger")
	class USphereComponent* GetInteractionTrigger() const { return InteractionTrigger; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	class UInteractionComponentBase* GetInteractionCommand() const { return InteractionCommand; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnWasInteractedWith();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnReEnableInteraction();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PropMesh;

	UPROPERTY(VisibleAnywhere, Category = "Interaction Trigger", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractionTrigger;

	// Class that implements the interaction for this prop
	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInteractionComponentBase> InteractionClass;

	// Interaction command for this prop
	UPROPERTY(VisibleAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UInteractionComponentBase* InteractionCommand;
};
