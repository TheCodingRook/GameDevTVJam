// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TimePickup.h"
#include "TimePickupRotating.generated.h"

/**
 * Custom TimePickup derived class to implement a rotating pyramid pickup that rotates through the 4 different 'ExtraTime' values (Gold/Silver/Copper/Nickel)
 */
UCLASS()
class GAMEDEVTVJAM_API ATimePickupRotating : public ATimePickup
{
	GENERATED_BODY()
	
public:
	ATimePickupRotating();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void RotatePyramid();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void PlayTimeWidgetAnimationRotating();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void WasCollected();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* Widget3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* Widget4;

	UPROPERTY(BlueprintReadWrite, Category = "Pyramid Settings", meta = (AllowPrivateAccess = "true"))
	FRotator StartingRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Pyramid Settings", meta = (AllowPrivateAccess = "true"))
	int ActiveWidgetIterator;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TArray<UWidgetComponent*> WidgetArray;

	TArray<float> ExtraTimeArray;

	TArray<class UMaterialInterface*> MaterialsArray;

	FTimerHandle PyramidRotator;

	UPROPERTY(BlueprintReadWrite, Category = "Pyramid Settings", meta = (AllowPrivateAccess = "true"))
	float DeltaZRotation = 90.f;

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Pyramid Settings")
	void UpdatePyramid();



};
