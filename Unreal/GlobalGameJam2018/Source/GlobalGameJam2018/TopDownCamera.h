// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TopDownCamera.generated.h"

/**
 * 
 */

class APlayerCharacter;

UCLASS()
class GLOBALGAMEJAM2018_API ATopDownCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:
	ATopDownCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Camera boom positioning the camera beside the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<APlayerCharacter*> playerReferences;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FVector> playerLocations;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<float> distances;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float targetArmLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector offset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator rotation;
};
