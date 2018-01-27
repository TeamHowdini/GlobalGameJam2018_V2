// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShield.h"


// Sets default values
APlayerShield::APlayerShield()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.f;

	RotationSpeed = 10.f;
}

// Called when the game starts or when spawned
void APlayerShield::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}