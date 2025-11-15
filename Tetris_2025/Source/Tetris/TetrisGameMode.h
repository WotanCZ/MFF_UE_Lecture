// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TetrisBlock.h"
#include "InputActionTypes.h"

#include "TetrisGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void ProcessPlayerInput(EInputActionType Value);

	void TetrisGameTick();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATetrisBlock> BlockClassToSpawn;

	UPROPERTY()
	TArray<ATetrisBlock*> Board;

	UPROPERTY()
	FTimerHandle GameTickTimerHandle;
	
};
