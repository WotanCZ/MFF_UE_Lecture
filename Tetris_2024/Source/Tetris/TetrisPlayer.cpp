// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPlayer.h"

// Engine include
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

	check(DefaultMappingContext);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	check(PlayerController);
	
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()
			))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		PlayerController->SetInputMode(FInputModeGameOnly{});
	}
}

void ATetrisPlayer::MoveBlockAction(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("MoveBlock %f"), Value.Get<float>());
	float MoveDir = Value.Get<float>();

	OnGameInputRequested.ExecuteIfBound(
		MoveDir < 0.f ?
		EInputActionTypes::MoveBlockLeft :
		EInputActionTypes::MoveBlockRight
	);
}

void ATetrisPlayer::PlaceBlockAction(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Place %d"), Value.Get<bool>());

	bool bPlaceBlock = Value.Get<bool>();

	OnGameInputRequested.ExecuteIfBound(
		bPlaceBlock ?
		EInputActionTypes::PlaceBlock :
		EInputActionTypes::Undefined
	);
}

void ATetrisPlayer::RotateBlockAction(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotate %d"), Value.Get<bool>());
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

	checkf(MoveBlock, TEXT("Test"));
	checkf(PlaceBlock, TEXT("Test"));
	checkf(RotateBlock, TEXT("Test"));

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::MoveBlockAction);

		EnhancedInputComponent->BindAction(PlaceBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::PlaceBlockAction);
		EnhancedInputComponent->BindAction(PlaceBlock, ETriggerEvent::Completed, this, &ATetrisPlayer::PlaceBlockAction);

		EnhancedInputComponent->BindAction(RotateBlock, ETriggerEvent::Triggered, this, &ATetrisPlayer::RotateBlockAction);
	}

}

