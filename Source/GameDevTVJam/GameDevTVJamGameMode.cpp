// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameDevTVJamGameMode.h"
#include "GameDevTVJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameDevTVJamGameMode::AGameDevTVJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGameDevTVJamGameMode::AddTime(float ExtraTime)
{
	CountDown += ExtraTime;
}