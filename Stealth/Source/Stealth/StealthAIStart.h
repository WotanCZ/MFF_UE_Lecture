// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/NavigationObjectBase.h"
#include "StealthAIStart.generated.h"

class AStealthAIController;
class AStealthAIPath;
class AStealthCharacter;
class UBehaviorTree;

/**
 * 
 */
UCLASS(Blueprintable)
class STEALTH_API AStealthAIStart : public ANavigationObjectBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay();

private:

	/** AI controller class to spawn. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AStealthAIController> ControllerClass;

	/** AI character class to spawn. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AStealthCharacter> CharacterClass;

	/** AI behavior that spawned AI should perform. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	UBehaviorTree* Behavior;

	/** AI path that spawned ai should follow. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	AStealthAIPath* Path;

};
