// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "TimePickup.generated.h"

UENUM(BlueprintType)
enum class ETimePickupType : uint8
{
	Gold UMETA(DisplayName = "Gold"),
	Silver UMETA(DisplayName = "Silver"),
	Copper UMETA(DisplayName = "Copper"),
	Nickel UMETA(DisplayName = "Nickel"),
	Pyramid UMETA(DisplayName = "Pyramid"),
	None UMETA(DisplayName = "None")
};

/**
 * Custom Pickup class for the time capsules/pickups the player can collect
 */
UCLASS()
class GAMEDEVTVJAM_API ATimePickup : public APickup
{
	GENERATED_BODY()

public:
	ATimePickup();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Pickup")

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void PlayTimeWidgetAnimation();
	
	class UMaterialInterface* Gold_Material;
	UMaterialInterface* Silver_Material;
	UMaterialInterface* Copper_Material;
	UMaterialInterface* Nickel_Material;

	class UStaticMesh* NarrowCapsule_Shape;
	UStaticMesh* Sphere_Shape;
	UStaticMesh* QuadPyramid_Shape;

	static float constexpr GOLD_TIME = 10.f;
	static float constexpr SILVER_TIME = 5.f;
	static float constexpr COPPER_TIME = 1.f ;
	static float constexpr NICKEL_TIME = -5.f;

protected:
	// Set the amount of extra time the pick up gives to the character (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra Time")
	float ExtraTime;

	// Set the default type to None so we force us to actually pick one specifically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Settings")
	ETimePickupType PickupType = ETimePickupType::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;

	// Pointer to the active widget of the pickup (this will be useful for derived pyramid pickup)
	UPROPERTY(BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* ActiveWidget;

#if WITH_EDITORONLY_DATA
	//~ Begin UObject Interface
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif 
};
