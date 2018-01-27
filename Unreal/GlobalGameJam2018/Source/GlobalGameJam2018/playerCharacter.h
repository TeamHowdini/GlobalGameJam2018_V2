// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "playerCharacter.generated.h"

class ATopDownCamera;

UCLASS(config = Game)
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	////////////////////////////////////////////
	///UPROPERIES
	////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = Movement)
		float MovementDeadZone = 0.1f;

	UPROPERTY(EditAnywhere, Category = Tweakable)
		int StartHealth = 5;

	////////////////////////////////////////////
	///UFUNCTIONS
	////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = Health)
		void SetHealth(int NewHealth) { CurrentHealth = NewHealth; }

	UFUNCTION(BlueprintCallable, Category = Health)
		const int GetHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = Health)
		int IncrementHealth(int HealthIncrease) { return CurrentHealth += HealthIncrease; }

	UFUNCTION(BlueprintCallable, Category = Health)
		int DecrementHealth(int HealthDecrease) { return CurrentHealth -= HealthDecrease; }
	
	UFUNCTION(BlueprintImplementableEvent)
		void PressPull();

	UFUNCTION(BlueprintImplementableEvent)
		void PressPush();

protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	int CurrentHealth;

	ATopDownCamera* MainCamera;

	FVector AimDirection;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

public:

	//Gets the camera reference and exits the game if no valid camera is setup
	void SetupCameraReference();

	virtual void Tick(float DeltaTime) override;

	void BindPull();
	void BindPush();
	
};