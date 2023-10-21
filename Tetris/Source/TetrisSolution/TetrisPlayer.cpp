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
	PrimaryActorTick.bCanEverTick = true;

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
	float MoveDir = Value.Get<float>();

	EInputActionTypes Direction = EInputActionTypes::Undefined;
	if (MoveDir < 0.f)
	{
		Direction = EInputActionTypes::MoveBlockLeft;
	}
	else if (MoveDir > 0.f)
	{
		Direction = EInputActionTypes::MoveBlockRight;
	}

	// MoveDir: -1 = Left, +1 = Right
	OnGameInputRequested.ExecuteIfBound(Direction);
}

void ATetrisPlayer::MoveBlockDownAction(const FInputActionValue& Value)
{
	OnGameInputRequested.ExecuteIfBound(Value.Get<bool>() ? EInputActionTypes::MoveBlockDown : EInputActionTypes::Undefined);
}

void ATetrisPlayer::RotateBlockAction(const FInputActionValue& Value)
{
	OnGameInputRequested.ExecuteIfBound(EInputActionTypes::RotateBlock);
}

// Called every frame
void ATetrisPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATetrisPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ensureAlwaysMsgf(MoveBlock, TEXT("MoveBlock action is not assigned!"));
	ensureAlwaysMsgf(MoveBlockDown, TEXT("MoveBlockDown action is not assigned!"));
	ensureAlwaysMsgf(RotateBlock, TEXT("RotateBlock action is not assigned!"));

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