// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "InputActionTypes.h"
#include "TetrisGameMode.generated.h"

class ATetrisBlock;


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
};

/**
 * Game mode fo the Tetris clone game, contains the whole game logic
 */
UCLASS()
class TETRISSOLUTION_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	/** Initialize the game */
	UFUNCTION(BlueprintCallable)
	void InitNewGame();

	/** Timer callback function, Tetris game tick */
	UFUNCTION()
	void TetrisGameTick();

private:
	/** Update the "Display" with current internal board representation */
	void UpdateBoard();

	/** Detects filled lines, clears them, and updates the internal board representation */
	void CheckForLineFill();

	/** Places the falling piece on its current position */
	void PlacePiece();

	/** Picks random piece and places it on the top */
	void SetupNewPiece();

	/** Update the game score and optionally make the game harder */
	void UpdateScore();

	/** Callback function from the bound delegate to process player's input */
	void ProcessPlayerInput(EInputActionTypes InputType);

	/** Get FColor from the internal board color representation */
	FColor DecodeBlockColor(uint8 TetrisBlockType);

	/** Tries to place piece on given location with given rotation, 1 when piece can be placed, 0 otherwise */
	uint8 CanPlacePiece(int32 PieceX, int32 PieceY, uint8 PieceRotation);

	/** Returns piece's local index in the piece representation, with respect to the given rotation */
	uint8 GetIndexBasedOnRotation(uint8 PosX, uint8 PosY, uint8 CurrentRotation);

private:
	/** Handle to interact with the game tick timer */
	UPROPERTY(VisibleInstanceOnly)
	FTimerHandle GameTickTimerHandle;

	/** ATetrisBlock blueprint actor reference */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATetrisBlock> BlockClassToSpawn;

	/** Array of actors representing the "Display" */
	UPROPERTY(VisibleInstanceOnly)
	TArray<ATetrisBlock*> Board;

	/** Array of vlaues representing block types (0-8) */
	UPROPERTY(VisibleInstanceOnly)
	TArray<uint8> InternalBoard;

	/** Array to hold y coordinate of possible lines formed during gameplay */
	UPROPERTY(VisibleInstanceOnly)
	TArray<uint8> FilledLines;

	UPROPERTY(EditAnywhere)
	uint8 BoardWidth = 12;

	UPROPERTY(EditAnywhere)
	uint8 BoardHeight = 20;

	/** Ticks per second: 1s / 20 = 50ms */
	UPROPERTY(EditAnywhere)
	int32 TicksPerSecond = 20;

	/** Move the falling piece down each X ticks */
	UPROPERTY(EditAnywhere)
	uint8 MoveBlockDownTicks = 10;

	/** Just a counter to track down the delay between moving the falling piece down */
	UPROPERTY()
	uint8 CurrentTick = 0;

	/** Player's accumulated score */
	UPROPERTY()
	uint64 Score = 0;

	/** Number of blocks the player placed */
	UPROPERTY()
	uint32 PlacedBlocks = 0;

	uint8 bMoveLeft : 1;
	uint8 bMoveRight : 1;
	uint8 bMoveDown : 1;
	uint8 bRotate : 1;

	/** Data representation of the falling piece */
	FFallingPiece FallingPiece;

	/** Array of possible tetris pieces */
	TArray<FTetrisPiece> TetrisPieces;	
};
