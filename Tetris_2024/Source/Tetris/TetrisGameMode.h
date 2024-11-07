// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionTypes.h"
#include "TetrisBlock.h"

#include "TetrisGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ProcessPlayerInput(EInputActionTypes Value);

	UFUNCTION()
	void TetrisGameTick();

private:
	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle GameTickHandle;

	UPROPERTY(EditAnywhere)
	int32 TicksPerSecond = 20;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATetrisBlock> BlockClassToSpawn;

	UPROPERTY(VisibleInstanceOnly)
	TArray<ATetrisBlock*> Board;

	UPROPERTY(EditAnywhere)
	uint8 BoardWidth = 12;

	UPROPERTY(EditAnywhere)
	uint8 BoardHeight = 20;
	
};
