// Copyright (c) 2018 Team Howdini.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TopDownCamera.generated.h"

class APlayerCharacter;

UCLASS()
class GLOBALGAMEJAM2018_API ATopDownCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	ATopDownCamera();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
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
	float armMinLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float armMaxLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector offset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator rotation;
};
