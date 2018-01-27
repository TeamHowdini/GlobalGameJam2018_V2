// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Instances/MainGameInstance.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuPawn.generated.h"



UCLASS()
class GLOBALGAMEJAM2018_API AMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void StartPressed();

	void NextLevelPressed();

	UFUNCTION(BlueprintCallable, Category = "Set Pawn Id")
	void SetId(int idp);

	UFUNCTION(BlueprintCallable, Category = "Set Pawn Id")
	bool GetEnabled() { return IsEnabled;  }

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsEnabled = false;

private:
	UMainGameInstance* GameInstance;

	int Id = 0;
};
