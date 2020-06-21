// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActor.h"
#include "TriggerPlatform.generated.h"

/**
 * Custom class to implement a trigger platform 
 */
UCLASS()
class GAMEDEVTVJAM_API ATriggerPlatform : public ATriggerActor
{
	GENERATED_BODY()

public:

	ATriggerPlatform();

	UFUNCTION()
	void NotifyTriggerPlatformBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void NotifyTriggerPlatformEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Platform movement")
	void PressPlatform();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Platform movement")
	void DepressPlatform();

	UFUNCTION(BlueprintCallable)
	class UStaticMeshComponent* GetMesh();

	void BeginPlay() override;

	class UMaterialInterface* Blue_Material;
	UMaterialInterface* Red_Material;
	UMaterialInterface* Green_Material;

protected:
	// Store the relative position of the platform's mesh
	//UPROPERTY(BlueprintReadWrite, Category = "Platform movement")
	//FVector StartingRelativeLocation;

	// How much to press the platform by (vertical movement intended here)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform movement")
	float PlatformZOffset;

	// A collision box that is just used to give the platform more volume and for 
	// simple overlap events to work properly
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionVolume;

	// The material instance the mesh of this TriggerPlatform is using
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	// Array of actors to store the actors that overlap this platform and can activate it
	TArray<AActor*> OverlappingActors;
};
