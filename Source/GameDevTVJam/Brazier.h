// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TriggerableActor.h"
#include "Brazier.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ABrazier : public ATriggerableActor
{
	GENERATED_BODY()

public:

	ABrazier();
	
	void BeginPlay() override;
	void PostLoad() override;
	
	UFUNCTION(BlueprintCallable, Category = "Brazier Settings", meta = (CallinEditor = true))
	void NativeToggleFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brazier Settings")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brazier Settings")
	class UParticleSystemComponent* Fire;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brazier Settings")
	class UPointLightComponent* Light;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Brazier Settings")
	bool bIsLit = true;

};
