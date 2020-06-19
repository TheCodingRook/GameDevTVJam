// Game developed by CodingRook for GameDev.TV's 2020 Game Jam. All rights reserved.


#include "GameDevTVJamStatics.h"

AGameDevTVJamGameMode* UGameDevTVJamStatics::GetGameDevTVJamGameMode(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World->GetAuthGameMode<AGameDevTVJamGameMode>();
}

UMyGameInstance* UGameDevTVJamStatics::GetMyGameInstance(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World->GetGameInstanceChecked<UMyGameInstance>();
}

AGameDevTVJamCharacter* UGameDevTVJamStatics::GetGameDevTVJamCharacter(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return Cast<AGameDevTVJamCharacter>(World->GetFirstPlayerController()->GetCharacter());
}

APlayerController* UGameDevTVJamStatics::GetGameDevTVJamController(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World->GetFirstPlayerController();
}

UGameHUDWidget* UGameDevTVJamStatics::GetGameHUD(const UObject* WorldContextObject)
{
	return GetGameDevTVJamGameMode(WorldContextObject)->GetGameHUD();
}
