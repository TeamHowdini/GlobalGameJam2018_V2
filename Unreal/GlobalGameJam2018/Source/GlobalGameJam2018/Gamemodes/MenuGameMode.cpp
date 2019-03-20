// Copyright (c) 2018 Team Howdini.

#include "MenuGameMode.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

AMenuGameMode::AMenuGameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMenuGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
