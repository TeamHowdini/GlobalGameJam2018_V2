// Copyright (c) 2018 Team Howdini.

#pragma once

#include "Instances/MainGameInstance.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuPawn.generated.h"

UCLASS()
class GLOBALGAMEJAM2018_API AMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMenuPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BackPressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
