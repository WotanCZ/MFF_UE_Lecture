// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectShooterBlankGameMode.h"
#include "ProjectShooterBlankCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectShooterBlankGameMode::AProjectShooterBlankGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
