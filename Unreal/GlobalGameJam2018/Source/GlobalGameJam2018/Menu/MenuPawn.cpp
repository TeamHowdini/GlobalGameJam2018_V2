// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPawn.h"

#include "Engine.h"

#include <assert.h>


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

	if (GetWorld())
	{
		UGameInstance* BasicGameInstance = Cast<UGameInstance>(GetWorld()->GetGameInstance());


		GameInstance = Cast<UMainGameInstance>(BasicGameInstance);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Not Called"));
	}
	
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

	InputComponent->BindAction("X_Button", IE_Pressed, this, &AMenuPawn::NextLevelPressed);

}

void AMenuPawn::SetId(int idp)
{
	Id = idp; // ye idk
}

void AMenuPawn::StartPressed()
{
	if (GameInstance)
		GameInstance->StartButtonPressed(Id);

	IsEnabled = !IsEnabled;
}

void AMenuPawn::NextLevelPressed() 
{
	if (GameInstance)
		GameInstance->PlayerNextLevelPressed();
}