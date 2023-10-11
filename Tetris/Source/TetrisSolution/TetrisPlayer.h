// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Include
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Project Includes
#include "InputActionTypes.h"

// This Include
#include "TetrisPlayer.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


DECLARE_DELEGATE_OneParam(FOnGameInputRequested, EInputActionTypes);

UCLASS()
class TETRISSOLUTION_API ATetrisPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATetrisPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void MoveBlockAction(const FInputActionValue& Value);

	/** Called for looking input */
	void PlaceBlockAction(const FInputActionValue& Value);

	/** Called for looking input */
	void RotateBlockAction(const FInputActionValue& Value);

	/** Called for looking input */
	void RestartGameAction(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move block Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveBlock;

	/** Place block Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlaceBlock;

	/** Rotate block Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateBlock;

	/** Restart game Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RestartGame;

public:
	FOnGameInputRequested OnGameInputRequested;
};
