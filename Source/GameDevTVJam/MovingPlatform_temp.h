// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform_temp.generated.h"

UCLASS()
class GAMEDEVTVJAM_API AMovingPlatform_temp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform_temp();

	void PostLoad() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere)
	//class UActorListComponent* ActorListComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
