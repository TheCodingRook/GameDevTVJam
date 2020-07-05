// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PainBox.generated.h"

static float constexpr PainBoxDamage = 1.f;

UCLASS()
class GAMEDEVTVJAM_API APainBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APainBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CollisionShape Properties", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBillboardComponent* SpriteComponent;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
