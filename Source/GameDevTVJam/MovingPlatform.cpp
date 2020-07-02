// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "MovingPlatform.h"
#include "PuzzleComponent.h"
#include "MyTriggerBox.h"
#include "TriggerActor.h"
#include "ActorListComponent.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	SetRootComponent(Platform);

	Puzzle = CreateDefaultSubobject<UPuzzleComponent>("Puzzle");

	// Initialize some movement settings here
	SpeedMultiplier = 1.f;
	OriginalPlayDirection = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Movement settings
	StartingLocation = GetActorLocation();
	LERP_StartingLocation = StartingLocation;

	//~ Puzzle elements setup

	for (AActor* LinkedActor : Puzzle->GetActorsList())
	{
		// Deal with linked actors that spawn a PuzzleElement dynamically that this MovingPlatform is to be linked with
		if (LinkedActor->ActorHasTag(FName("SpawnsPuzzleElement")))
		{
			// deal with linking spawned puzzle elements at runtime
		}
	}

	for (UPuzzleElementComponent* PuzzleElement : Puzzle->GetPuzzleElementsList())
	{
		// Distinguish between trigger boxes and TriggerPlatforms
		if (AMyTriggerBox* TriggerBox = Cast<AMyTriggerBox>(PuzzleElement->GetOwner()))
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &AMovingPlatform::StartMovingPlatform);
		}
		else if (ATriggerActor* TriggerActor = Cast<ATriggerActor>(PuzzleElement->GetOwner()))
		{
			PuzzleElement->OnPuzzleElementActivated.AddDynamic(this, &AMovingPlatform::AttemptChangeMovement);
			PuzzleElement->OnPuzzleElementDeactivated.AddDynamic(this, &AMovingPlatform::AttemptChangeMovement);
		}
	}

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingPlatform::PostLoad()
{
	Super::PostLoad();

	TInlineComponentArray<UActorListComponent*> ActorListComponent;
	GetComponents(ActorListComponent);

	TInlineComponentArray<UPuzzleComponent*> PuzzleComponent;
	GetComponents(PuzzleComponent);

	UE_LOG(LogTemp, Warning, TEXT("Found %i PuzzleComponents in %s"), PuzzleComponent.Num(), *GetName())
	UE_LOG(LogTemp, Warning, TEXT("Found %i ActorListComponents in %s"), ActorListComponent.Num(), *GetName())

	PuzzleComponent[0]->SetActorsList(ActorListComponent[0]->ActorList);

}

void AMovingPlatform::AttemptChangeMovement(EPuzzleElementType ElementType)
{
	switch (ElementType)
	{
	case EPuzzleElementType::NOSwitch:
		UE_LOG(LogTemp, Warning, TEXT("The implementation for the a Normally-Open switch on a moving platform is not valid yet!"))
		break;
	case EPuzzleElementType::Toggle:
		if ((DistanceToTravel.Y != 0 && DistanceToTravel.Z == 0) || (DistanceToTravel.Y == 0 && DistanceToTravel.Z != 0))
		{
			LERP_StartingLocation.X = StartingLocation.X;

			// If platform is moving horizontally
			if (DistanceToTravel.Y != 0)
			{
				// Adjust the LERP starting location in terms of Y
				LERP_StartingLocation.Y = LERP_StartingLocation.Y + DistanceTraveled.Y;
				LERP_StartingLocation.Z = StartingLocation.Z;

				// Set the new playback position for the timeline based on portion of distanced traveled on Z axis
				TimelineNewPlaybackPosition = FMath::Abs(DistanceTraveled.Z / DistanceToTravel.Y) * NativeTimeline->GetTimelineLength();
			}
			else
			{
				// Adjust the LERP starting location in terms of Z
				LERP_StartingLocation.Y = StartingLocation.Y;
				LERP_StartingLocation.Z = StartingLocation.Z + DistanceTraveled.Z;

				// Set the new playback position for the timeline based on portion of distanced traveled on Y axis
				TimelineNewPlaybackPosition = FMath::Abs(DistanceTraveled.Y / DistanceToTravel.Z) * NativeTimeline->GetTimelineLength();
			}
				
			// Flip the Y/Z in DistanceToTravel
			float DistanceToTravel_Y_temp = DistanceToTravel.Y;
			float DistanceToTravel_Z_temp = DistanceToTravel.Z;
			DistanceToTravel.Y = -DistanceToTravel_Z_temp;
			DistanceToTravel.Z = -DistanceToTravel_Y_temp;

			ChangeDirection(TimelineNewPlaybackPosition);
		}
		break;
	case EPuzzleElementType::NOSwitch_Rotator:
		UE_LOG(LogTemp, Warning, TEXT("The implementation for the a Normally-Open Rotator switch on a moving platform is not valid yet!"))
		break;
	case EPuzzleElementType::Toggle_Rotator:
		ChangeRotation();
		break;
	case EPuzzleElementType::Type_None:
		break;
	default:
		break;
	}
}