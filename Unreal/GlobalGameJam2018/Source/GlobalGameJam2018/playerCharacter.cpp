// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "playerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDownCamera.h"
#include "Engine.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//Set player health
	CurrentHealth = StartHealth;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; 	
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Pull", IE_Pressed, this, &APlayerCharacter::BindPull);
	PlayerInputComponent->BindAction("Push", IE_Pressed, this, &APlayerCharacter::BindPush);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupCameraReference();
	
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	if ((Controller != NULL) && (Rate != 0.0f))
	{
		AimDirection.X = Rate;
	}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	if ((Controller != NULL) && (Rate != 0.0f))
	{
		AimDirection.Y = Rate;
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Get camera forward
		const FRotator Rotation = MainCamera->CameraBoom->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector relative to world
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Get camera forward
		const FRotator Rotation = MainCamera->CameraBoom->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector relatie to world
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::SetupCameraReference() {
	TArray<AActor*> FoundCamera;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATopDownCamera::StaticClass(), FoundCamera);
	if (FoundCamera.Num() == 1) {
		MainCamera = Cast<ATopDownCamera>(FoundCamera[0]);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[ERROR] Please place one TopDownCamera BP in the scene!"));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit);
	}
	if (!MainCamera)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("[ERROR] Failed to cast to TopDownCamera!"));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CameraRotation = MainCamera->CameraBoom->GetComponentRotation();
	FRotator YawRotation(0.f, CameraRotation.Yaw, 0.f);
	AimRotation = YawRotation.RotateVector(FVector(AimDirection.X, AimDirection.Y, 0.f));
	AimRotation.Normalize();
	if (AimDirection.X || AimDirection.Y) 
	{
		SetActorRotation(FVector(AimDirection.X, AimDirection.Y, 0.f).Rotation() -YawRotation);
	}
}

void APlayerCharacter::BindPull()
{
	PressPull();
}

void APlayerCharacter::BindPush()
{
	PressPush();
}