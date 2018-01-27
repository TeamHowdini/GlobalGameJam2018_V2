// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "playerCharacter.h"
#include "Kismet/GameplayStatics.h"

ATopDownCamera::ATopDownCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bAutoActivate = true;
	CameraBoom->TargetArmLength = targetArmLength;

	GetCameraComponent()->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	GetCameraComponent()->bUsePawnControlRotation = false;
	GetCameraComponent()->bAutoActivate = true;

	armMinLength = 250;
	armMaxLength = 750;
}

void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();

}

void ATopDownCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraBoom->SetRelativeLocation(offset);
	CameraBoom->SetRelativeRotation(rotation);

	TArray<AActor*> foundActors;
	playerReferences.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), foundActors);
	for (int i = 0; i < foundActors.Num(); i++)
	{
		playerReferences.Add(Cast<APlayerCharacter>(foundActors[i]));
	}
}