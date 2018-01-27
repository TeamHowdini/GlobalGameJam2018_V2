// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include <assert.h> 

UMainGameInstance::UMainGameInstance() {
	// Asume that the game starts at the menu
	CurrentLevelIndex = 0;

	LevelArray.Add(TEXT("Menu_Level")); // Hardcoded menu deal with it
}

void UMainGameInstance::ChangeCurrentLevel(FName LevelName, bool ResetPlayerData) {
	CurrentLevelIndex = 0;

	for (int i = 0; i < LevelArray.Num(); i++) {
		if (LevelArray[i] == LevelName) {
			CurrentLevelIndex = i;

			UE_LOG(LogTemp, Warning, TEXT("Level changed to %i "), i);
		}
	}

	if (!ResetPlayerData)
		SavePlayerData();

	UGameplayStatics::OpenLevel((UObject*)this, LevelName);

	if (!ResetPlayerData)
		LoadPlayerData();

	

}

void UMainGameInstance::ChangeCurrentLevelToNext() {
	if (LevelArray.Num() == 0) {

		assert("LevelArray is empty.");
	}

	CurrentLevelIndex++;

	// LAST LEVEL DETECTION
	if ((int)CurrentLevelIndex >= LevelArray.Num()) {
		// If last level is exceeded, wrap to zero
		CurrentLevelIndex = 0;
	}

	SavePlayerData();

	UGameplayStatics::OpenLevel((UObject*)this, LevelArray[CurrentLevelIndex]);

	LoadPlayerData();

}

void UMainGameInstance::StartButtonPressed(unsigned int id) {
	IsPlayerConnected[id] = !IsPlayerConnected[id];
}


void UMainGameInstance::PlayerNextLevelPressed() 
{
	int NumberOfPlayersConnected = 0;

	for (int i = 0; i < 4; i++) {
		if (IsPlayerConnected[i])
			NumberOfPlayersConnected++;
	}

	if (NumberOfPlayersConnected > 0)
		ChangeCurrentLevelToNext();
}

///////////////////////////////////////////////////////////////////////////////////////////

void UMainGameInstance::SavePlayerData() {

}

void UMainGameInstance::LoadPlayerData() {

}