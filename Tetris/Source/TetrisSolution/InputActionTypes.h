// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Different states that the player can interact with the game
 */
enum class EInputActionTypes : uint8
{
	MoveBlockLeft = 0,
	MoveBlockRight,
	PlaceBlock,
	RotateBlock,
	Undefined
};