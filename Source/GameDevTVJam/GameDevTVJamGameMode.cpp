// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameDevTVJamGameMode.h"
#include "GameDevTVJamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameDevTVJamCharacter.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUDWidget.h"
#include "PauseMenuWidget.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

AGameDevTVJamGameMode::AGameDevTVJamGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AGameDevTVJamGameMode::PauseGame()
{
	// Pause the game
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// Pause music
	GameMusicAudioComponent->SetPaused(true);

	if (!PauseMenu)
	{
		PauseMenu = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuClass, FName("Pause Menu"));
		PauseMenu->AddToViewport();
	}

	else
	{
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
	}

	PauseMenu->LoadWidget();
}

void AGameDevTVJamGameMode::PlayerLost()
{
	// Stop timer
	bCanUpdateTimer = false;

	FTimerHandle DelayAfterDeath;
	// Call the helper function to broadcast the notifier after a delay
	GetWorldTimerManager().SetTimer(DelayAfterDeath, this, &AGameDevTVJamGameMode::RestartGame_HelperFunc, 2.f, false, -1.f);
}

void AGameDevTVJamGameMode::PlayerWon()
{
	// Stop ambient music
	if (GameMusicAudioComponent)
	{
		GameMusicAudioComponent->Stop();
	}

	if (VictoryMusic)
	{
		
		VictoryMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, VictoryMusic);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("You have not specified a victory music to play."));
	}

	GameHUD->PlayVictoryAnimation();

	// Short delay before we play victory dance/animation for player
	FTimerHandle DelayBeforeVictoryAnimation;
	// Call the helper function to handle character's victory animation
	GetWorldTimerManager().SetTimer(DelayBeforeVictoryAnimation, PlayerCharacter, &AGameDevTVJamCharacter::VictoryAnimation, 0.75f, false, -1.f);

	// Some delay after victory and before going back to main menu
	FTimerHandle DelayAfterVictory;
	// Call the helper function to broadcast the notifier after a delay
	GetWorldTimerManager().SetTimer(DelayAfterVictory, this, &AGameDevTVJamGameMode::RestartGame_HelperFunc, 12.f, false, -1.f);
}

void AGameDevTVJamGameMode::Tick(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	FrameCount++;

	if (bCanUpdateTimer && FrameCount >= FrameDelay && !PlayerCharacter->IsVictorious())
	{
		GameInstance->SetCountDown(GameInstance->GetCountDown() - ElapsedTime);
		GameHUD->UpdateRemainingTime(GameInstance->GetCountDown());

		// Reset the appropriate member fields
		FrameCount = 0;
		ElapsedTime = 0;

		if (GameInstance->GetCountDown() <= 0)
		{
			PlayerCharacter->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			GameHUD->TimesUp();
			PlayerLost();
		}
	}
}

void AGameDevTVJamGameMode::BeginPlay()
{
	// Check for valid HUD
	if (!GameHUDClass)
	{
		UE_LOG(LogTemp, Error, TEXT("You have not defined a Widget Blueprint for the HUD"));
	}
	// Check for valid Pause Menu
	if (!PauseMenuClass)
	{
		UE_LOG(LogTemp, Error, TEXT("You have not defined a Widget Blueprint for the Pause Menu"));
	}

	if (GameMusic)
	{
		// Start music
		GameMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, GameMusic);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("You have not specified a music loop to play during gameplay"));
	}

	// Save down the gameplay framework references to character and game instance
	PlayerCharacter = Cast<AGameDevTVJamCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	GameHUD = CreateWidget<UGameHUDWidget>(GetWorld(),GameHUDClass,FName("Game HUD"));
	GameHUD->AddToViewport();

	// Are we starting after losing a life?
	if (GameInstance->GetCurrentLives() < GameInstance->GetStartingLives())
		//Load saved versions or set starting game data variables, depending on whether we start a fresh new game or not
	{
		GameInstance->LoadGameData();
	}
	else
	{
		GameInstance->ReachedSavePoint(false, FVector(0.f,0.f,0.f));
	}

	// Update HUD with game data variables
	GameHUD->UpdateRemainingLives(GameInstance->GetCurrentLives());
	GameHUD->UpdateCurrentLevel(GameInstance->GetCurrentLevel());
	GameHUD->UpdateKeysFound(GameInstance->GetSaveNumberOfKeys());
	GameHUD->UpdateTreasuresFound(GameInstance->GetSaveNumberOfTreasures());

	// Bind the FPlayerDied delegate
	PlayerCharacter->OnPlayerDied.AddDynamic(this, &AGameDevTVJamGameMode::PlayerLost);

	// Bind the FPlayerWon delegate
	PlayerCharacter->OnPlayerWon.AddDynamic(this, &AGameDevTVJamGameMode::PlayerWon);

}

void AGameDevTVJamGameMode::RestartGame_HelperFunc()
{
	if (GameInstance->GetCurrentLives() <= 1 || PlayerCharacter->IsVictorious())
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName("PuzzleRun2"));
		GameInstance->LostLife();
	}
}