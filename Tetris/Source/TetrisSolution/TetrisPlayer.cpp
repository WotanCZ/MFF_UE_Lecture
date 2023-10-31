// Fill out your copyright notice in the Description page of Project Settings.

// This Include
#include "TetrisPlayer.h"

// Engine Include
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


// Sets default values
ATetrisPlayer::ATetrisPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATetrisPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void ATetrisPlayer::MoveBlockAction(const FInputActionValue& Value)
{
	// Event Triggered - Value has to be either -1.f or 1.f
	// MoveDir: -1 = Left, +1 = Right
	float MoveDir = Value.Get<float>();
	
	OnGameInputRequested.ExecuteIfBound(MoveDir < 0.f ? EInputActionTypes::MoveBlockLeft : EInputActionTypes::MoveBlockRight);
}

void ATetrisPlayer::MoveBlockDownAction(const FInputActionValue& Value)
{
	// Value is True when the button is pressed, False otherwise
	bool bIsButtonPressed = Value.Get<bool>();

	OnGameInputRequested.ExecuteIfBound(bIsButtonPressed ? EInputActionTypes::MoveBlockDown : EInputActionTypes::Undefined);
}

void ATetrisPlayer::RotateBlockAction(const FInputActionValue& Value)
{
	// One shot action
	OnGameInputRequested.ExecuteIfBound(EInputActionTypes::RotateBlock);
}

// Called to bind functionality to input
void ATetrisPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make checks that the input actions are set up
	// check = assert: stops exectution
	check(MoveBlock);
	check(MoveBlockDown);
	check(RotateBlock);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move block action
		EnhancedInputComponent->BindAction(MoveBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::MoveBlockAction);

		// Place block action - detect press and hold
		EnhancedInputComponent->BindAction(MoveBlockDown, ETriggerEvent::Triggered, this, &ATetrisPlayer::MoveBlockDownAction);
		EnhancedInputComponent->BindAction(MoveBlockDown, ETriggerEvent::Completed, this, &ATetrisPlayer::MoveBlockDownAction);

		// Rotate block action
		EnhancedInputComponent->BindAction(RotateBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::RotateBlockAction);
	}
}