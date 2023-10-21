// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisBlock.h"
#include "InputActionTypes.h"
#include "TetrisGameMode.generated.h"


struct TETRISSOLUTION_API FFallingPiece
{	
	int32 PositionX = 0;
	int32 PositionY = 0;
	uint8 CurrentColor = 0;
	uint8 CurrentRotation = 0;
};

struct TETRISSOLUTION_API FTetrisPiece
{
	TArray<uint8> Matrix;

	FTetrisPiece() {};
	FTetrisPiece(TArray<uint8> InArray)
	{
		Matrix = InArray;
	}
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

	//UFUNCTION()
	//void LineClearTick();

private:
	void UpdateBoard();

	void CheckForLineFill();

	void PlacePiece();

	bool SetupNewPiece();

	void UpdateScore();

	void ProcessPlayerInput(EInputActionTypes InputType);

	FColor GetCurrentBlockColor(uint8 TetrisBlockType);

	uint8 CanPlacePiece(int32 PieceX, int32 PieceY, uint8 PieceRotation);

	uint8 GetIndexBasedOnRotation(uint8 px, uint8 py, uint8 CurrentRotation);

private:
	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle GameTickTimerHandle;

	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle LineClearTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATetrisBlock> BlockClassToSpawn;

	UPROPERTY(VisibleInstanceOnly)
	TArray<ATetrisBlock*> Board;

	UPROPERTY(VisibleInstanceOnly)
	TArray<uint8> InternalBoard;

	UPROPERTY(VisibleInstanceOnly)
	TArray<uint8> FilledLines;

	UPROPERTY(EditAnywhere)
	uint8 BoardWidth = 12;

	UPROPERTY(EditAnywhere)
	uint8 BoardHeight = 20;

	/** Ticks per second - 1s / 20 = 50ms */
	UPROPERTY(EditAnywhere)
	float TicksPerSecond = 20.f;

	UPROPERTY(EditAnywhere)
	uint8 MoveBlockDownTicks = 10;

	UPROPERTY(VisibleInstanceOnly)
	uint8 CurrentTick = 0;

	UPROPERTY(VisibleInstanceOnly)
	uint64 Score = 0;

	UPROPERTY(VisibleInstanceOnly)
	uint32 PlacedBlocks = 0;

	uint8 bMoveLeft : 1;
	uint8 bMoveRight : 1;
	uint8 bMoveDown : 1;
	uint8 bRotate : 1;

	uint8 ClearedLines = 0;

	
	FFallingPiece FallingPiece;
	TArray<FTetrisPiece> TetrisPieces;	
};
