// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "StealthPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AStealthPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AStealthPlayerController();

protected:

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

private: // Input

	void OnMoveTrigerred(const FInputActionValue& Value);

private: // Input

	/** MappingContext for gameplay */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GameplayMappingContext;

	/** Input action to move character forward / backward /left / right */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
};


