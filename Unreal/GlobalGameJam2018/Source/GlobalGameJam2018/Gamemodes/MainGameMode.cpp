// Copyright (c) 2018 Team Howdini.

#include "MainGameMode.h"

AMainGameMode::AMainGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
