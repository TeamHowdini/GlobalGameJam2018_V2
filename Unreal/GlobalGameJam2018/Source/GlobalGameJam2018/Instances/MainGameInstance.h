// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class GLOBALGAMEJAM2018_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TArray<FName> LevelArray;
	
	UPROPERTY(BlueprintReadOnly, Category = "Players")
	TArray<bool> IsPlayerConnected = {0, 0, 0, 0};

	void StartButtonPressed(unsigned int id);

	void PlayerNextLevelPressed();

private:
	void SavePlayerData();
	void LoadPlayerData();

private:
	unsigned int CurrentLevelIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void ChangeCurrentLevel(FName LevelName, bool ResetPlayerData);
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void ChangeCurrentLevelToNext();
};
