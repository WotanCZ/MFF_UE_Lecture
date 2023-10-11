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
	}
}

void ATetrisPlayer::MoveBlockAction(const FInputActionValue& Value)
{
	float MoveDir = Value.Get<float>();

	// MoveDir: -1 = Left, +1 = Right
	OnGameInputRequested.ExecuteIfBound(MoveDir > 0 ? EInputActionTypes::MoveBlockRight : EInputActionTypes::MoveBlockLeft);
}

void ATetrisPlayer::PlaceBlockAction(const FInputActionValue& Value)
{
	OnGameInputRequested.ExecuteIfBound(EInputActionTypes::PlaceBlock);
}

void ATetrisPlayer::RotateBlockAction(const FInputActionValue& Value)
{
	OnGameInputRequested.ExecuteIfBound(EInputActionTypes::RotateBlock);
}

void ATetrisPlayer::RestartGameAction(const FInputActionValue& Value)
{
	OnGameInputRequested.ExecuteIfBound(EInputActionTypes::RestartGame);
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

	UE_LOG(LogTemp, Warning, TEXT("What"));

	ensureAlwaysMsgf(MoveBlock, TEXT("MoveBlock action is not assigned!"));
	ensureAlwaysMsgf(PlaceBlock, TEXT("PlaceBlock action is not assigned!"));
	ensureAlwaysMsgf(RotateBlock, TEXT("RotateBlock action is not assigned!"));
	ensureAlwaysMsgf(RestartGame, TEXT("RestartBlock action is not assigned!"));

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move block action
		EnhancedInputComponent->BindAction(MoveBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::MoveBlockAction);

		// Place block action
		EnhancedInputComponent->BindAction(PlaceBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::PlaceBlockAction);

		// Rotate block action
		EnhancedInputComponent->BindAction(RotateBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::RotateBlockAction);

		// restart game action
		EnhancedInputComponent->BindAction(RestartGame, ETriggerEvent::Triggered, this, &ATetrisPlayer::RestartGameAction);
	}
}

