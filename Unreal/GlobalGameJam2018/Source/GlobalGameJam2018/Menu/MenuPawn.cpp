// Copyright (c) 2018 Team Howdini.

#include "MenuPawn.h"
#include "Engine.h"

// Sets default values
AMenuPawn::AMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMenuPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("A_Button", IE_Pressed, this, &AMenuPawn::StartPressed);
	InputComponent->BindAction("A_Button", IE_Released, this, &AMenuPawn::EndPressed);
	InputComponent->BindAction("B_Button", IE_Pressed, this, &AMenuPawn::BackPressed);
}

void AMenuPawn::StartPressed_Implementation()
{

}

void AMenuPawn::EndPressed_Implementation()
{

}

void AMenuPawn::BackPressed_Implementation()
{

}
