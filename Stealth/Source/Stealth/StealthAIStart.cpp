// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthAIStart.h"

#include "StealthAIController.h"
#include "StealthAIPath.h"
#include "StealthCharacter.h"

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>

void AStealthAIStart::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(ControllerClass) || !IsValid(CharacterClass) || !IsValid(Behavior))
	{
		return;
	}
}
