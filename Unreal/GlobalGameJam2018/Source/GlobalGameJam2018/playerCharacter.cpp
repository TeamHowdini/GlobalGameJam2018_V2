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

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 650.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Pull", IE_Pressed, this, &APlayerCharacter::BindPull);
	PlayerInputComponent->BindAction("Push", IE_Pressed, this, &APlayerCharacter::BindPush);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupCameraReference();
	CurrentHealth = StartHealth;
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	if ((Controller != NULL) && (Rate != AimDirection.X))
	{
		// 	if (GEngine)
		//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Turn: ") + FString::FromInt(AimDirection.X*1000));
		AimDirection.X = Rate;
	}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	if ((Controller != NULL) && (Rate != AimDirection.Y))
	{
		/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Look: " + FString::FromInt(AimDirection.Y*1000)));*/
		AimDirection.Y = Rate;
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = MainCamera->CameraBoom->GetComponentRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		FRotator Rotation = MainCamera->CameraBoom->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
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

	if (!AimDirection.IsNearlyZero(MovementDeadZone)) {
		FRotator AimRotation = FVector(AimDirection.X, AimDirection.Y, 0.f).Rotation();
		FRotator CameraRotation = MainCamera->CameraBoom->GetComponentRotation();
		FRotator YawRotation(0.f, CameraRotation.Yaw, 0.f);
		FRotator NewRotation = UKismetMathLibrary::ComposeRotators(AimRotation, YawRotation);

		SetActorRotation(AimRotation - YawRotation);
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