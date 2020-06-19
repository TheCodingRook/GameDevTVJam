// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "SavePoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameDevTVJamCharacter.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameDevTVJamGameMode.h"
#include "GameHUDWidget.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our SaveTrigger collision box
	SaveTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Save Point Trigger"));
	SetRootComponent(SaveTrigger);

	// Create our BlockingTrigger collision box
	BlockingTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Blocking Trigger"));
	SetRootComponent(SaveTrigger);

	// Create the SavePoint's mesh (useful when this is a mid-level SavePoint and needs to be visible)
	SavePointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Save Point Mesh"));
	SavePointMesh->SetupAttachment(SaveTrigger);
}

void ASavePoint::OnSaveTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsActive)
	{
		if (Cast<AGameDevTVJamCharacter>(OtherActor))
		{
			UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
			GameInstance->ReachedSavePoint(bIsNewLevel, SpawnVectorOffset);

			if (bIsNewLevel)
			{
				Cast<AGameDevTVJamGameMode>(UGameplayStatics::GetGameMode(this))->GetGameHUD()->UpdateCurrentLevel(GameInstance->GetCurrentLevel());
				bIsActive = false;
			}
		}
	}
}

void ASavePoint::OnBlockingTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsNewLevel)
	{
		if (Cast<AGameDevTVJamCharacter>(OtherActor))
		{
			SaveTrigger->SetCollisionProfileName(FName("BlockAllDynamic"));
		}
	}
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	SaveTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::OnSaveTriggerOverlap);
	BlockingTrigger->OnComponentEndOverlap.AddDynamic(this, &ASavePoint::OnBlockingTriggerEndOverlap);
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
