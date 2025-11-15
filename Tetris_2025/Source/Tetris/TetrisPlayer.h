// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputActionTypes.h"

#include "TetrisPlayer.generated.h"

DECLARE_DELEGATE_OneParam(FOnGameInputRequested, EInputActionType);

UCLASS()
class TETRIS_API ATetrisPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATetrisPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void RotateBlockAction(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* TetrisMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RotateBlock;

	FOnGameInputRequested OnGameInputRequested;
};
