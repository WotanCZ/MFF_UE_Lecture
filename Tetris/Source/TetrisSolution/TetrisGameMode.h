// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisBlock.h"
#include "InputActionTypes.h"
#include "TetrisGameMode.generated.h"


UENUM(Blueprintable)
enum class EDirection : uint8
{
	Down = 0,
	Left,
	Right,
	DirectionCount
};


UENUM(Blueprintable)
enum class EBlockTypes : uint8
{
	Red = 0,
	Green,
	Blue,
	Yellow,
	Orange,
	Cyan,
	Purple,
	BlockColorNum
};

struct FFallingBlock
{
	FIntPoint Positions[4];
	bool bInitialized = false;
	EBlockTypes BlockType = EBlockTypes::BlockColorNum;
	FLinearColor BlockColor = FLinearColor::Black;
};

/**
 * 
 */
UCLASS()
class TETRISSOLUTION_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION()
	void TetrisGameTick();

	void MoveBlock(const EDirection Direction, const EBlockTypes BlockColor);

	void RotateBlock(const EDirection Direction, const EBlockTypes BlockColor);

	void PutBlockDown();

	void MoveBlockCalled(float Dir);

private:
	void UpdateBoard();

	void CheckForLineFill();

	void ProcessPlayerInput(EInputActionTypes InputType);

private:
	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle GameTickTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATetrisBlock> BlockClassToSpawn;

	UPROPERTY(VisibleInstanceOnly)
	TArray<ATetrisBlock*> Board;

	UPROPERTY(EditAnywhere)
	uint8 BoardWidth = 10;

	UPROPERTY(EditAnywhere)
	uint8 BoardHeight = 20;

	UPROPERTY(EditAnywhere)
	float TicksPerSecond = 2.f;

	UPROPERTY(VisibleInstanceOnly)
	uint64 Score = 0;

	
	FFallingBlock CurrentBlock;
	TArray<FFallingBlock> TetrisBlocks;

	
	
};
