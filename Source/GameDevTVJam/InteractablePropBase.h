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

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnWasInteractedWith();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnReEnableInteraction();

	UFUNCTION()
	void OnPropBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnPropEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	/* Function to determine whether this interaction requires another prop in order to work
	 * This returns true by default, for props that do not require anything else;
	 * Override if the prop requires a combination prop for an interaction!
	 */
	//UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	virtual bool ComboQuery(class AGameDevTVJamCharacter* PlayerCharacter);

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

	// Class that implements the interaction widget for this prop
	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UInteractionWidget> InteractionPromptClass;

	// Pointer to Interaction prompt for this prop
	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UInteractionWidget* InteractionPrompt;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FVector CustomWidgetOffset;

	// Is it necessary for this prop to display an interaction prompt?
	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool bIsWidgetNecessary = true;

	/** Sound to play when Prop is interacted with (leave empty in Blueprint if not needed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	class USoundBase* InteractionSound;

private:
	void SetPromptScreenLocation();
};
