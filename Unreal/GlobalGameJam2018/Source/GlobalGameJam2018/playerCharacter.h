// Copyright (c) 2018 Team Howdini.

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

	//Gets the camera reference and exits the game if no valid camera is setup
	void SetupCameraReference();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void BindPull();
	void BindPush();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

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

	UFUNCTION(BlueprintImplementableEvent)
	void BackPressed();

public:
	UPROPERTY(EditAnywhere, Category = Movement)
	float MovementDeadZone = 0.1f;

	UPROPERTY(EditAnywhere, Category = Tweakable)
	int StartHealth = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scuffed)
	FVector AimRotation;
	
	int CurrentHealth;

	ATopDownCamera* MainCamera;

	FVector AimDirection;
};