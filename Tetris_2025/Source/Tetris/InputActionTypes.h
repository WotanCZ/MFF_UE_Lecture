#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EInputActionType : uint8
{
	MoveBlockLeft,
	MoveBlockRight,
	RotateBlock,
	MoveBlockDown,
	Undefined
};
