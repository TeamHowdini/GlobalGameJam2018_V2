// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerShield.generated.h"

UCLASS()
class GLOBALGAMEJAM2018_API APlayerShield : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tweakable Variable")
		float Health;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tweakable Variable")
		float RotationSpeed;

};