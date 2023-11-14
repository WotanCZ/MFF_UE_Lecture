// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

#include "TetrisPlayer.h"
#include "TetrisBlock.h"

#include "Kismet/GameplayStatics.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Bind to the input delegate
	if (UWorld* World = GetWorld())
	{
		if (ATetrisPlayer* PlayerPawn = Cast<ATetrisPlayer>(UGameplayStatics::GetPlayerPawn(World, 0)))
		{
			PlayerPawn->OnGameInputRequested.BindUObject(this, &ATetrisGameMode::ProcessPlayerInput);
		}
	}
	
	// Initialize Tetris piece types
	{
		// I
		FTetrisPiece Piece;
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 0, 0,
			2, 2, 2, 2,
			0, 0, 0, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// O
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 0, 0,
			0, 3, 3, 0,
			0, 3, 3, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// T
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 0, 0,
			4, 4, 4, 0,
			0, 4, 0, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// J
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 5, 0,
			0, 0, 5, 0,
			0, 5, 5, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// L
		Piece.Matrix = TArray<uint8>
		{
			0, 6, 0, 0,
			0, 6, 0, 0,
			0, 6, 6, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// S
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 0, 0,
			0, 7, 7, 0,
			7, 7, 0, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);

		// Z
		Piece.Matrix = TArray<uint8>
		{
			0, 0, 0, 0,
			8, 8, 0, 0,
			0, 8, 8, 0,
			0, 0, 0, 0,
		};
		TetrisPieces.Push(Piece);
	}

	// Clear current player's input
	bMoveDown = false;
	bMoveRight = false;
	bMoveLeft = false;
	bRotate = false;

	// Init a new game
	InitNewGame();
}

void ATetrisGameMode::InitNewGame()
{
	// Init board and spawn actors representing "display"
	Board.Init(nullptr, BoardWidth * BoardHeight);
	InternalBoard.Init(0, BoardWidth * BoardHeight);

	uint8 BlockSize = 100;

	if (UWorld* World = GetWorld())
	{
		// We're about to spawn an actor, so perform a sanity check (if assigned from the Editor)
		check(BlockClassToSpawn);

		// Spawn the board
		for (uint8 y = 0; y < BoardHeight; ++y)
		{
			for (uint8 x = 0; x < BoardWidth; ++x)
			{
				uint8 CurrentIdx = y * BoardWidth + x;

				FVector Location = FVector(x * BlockSize, 0, y * BlockSize);
				
				Board[CurrentIdx] = World->SpawnActor<ATetrisBlock>(BlockClassToSpawn, Location, FRotator::ZeroRotator);
				
				bool bIsBorder = (x == 0 || x == BoardWidth - 1 || y == 0);

				Board[CurrentIdx]->SetBlockColor(bIsBorder ? FColor::White : FColor::Black);
				InternalBoard[CurrentIdx] = (bIsBorder ? 1 : 0);
			}
		}

		// Spawn the floor
		// Watch out! Whis way you will lose access to the floor actor!
		ATetrisBlock* Floor = World->SpawnActor<ATetrisBlock>(BlockClassToSpawn, FVector(450, 0, -BlockSize), FRotator::ZeroRotator);
		Floor->SetActorScale3D(FVector(50, 50, 1));
		Floor->SetBlockColor(FColor::White);

		// Clear score
		Score = 0;

		// Setup the first piece
		SetupNewPiece();

		// Set game timer
		World->GetTimerManager().SetTimer(GameTickTimerHandle, this, &ATetrisGameMode::TetrisGameTick, 1.f / TicksPerSecond, true);
	}	
}

void ATetrisGameMode::TetrisGameTick()
{
	// Process player's input
	if (bMoveLeft)
	{
		FallingPiece.PositionX -= CanPlacePiece(FallingPiece.PositionX - 1, FallingPiece.PositionY, FallingPiece.CurrentRotation);
		bMoveLeft = false;
	}
	if (bMoveRight)
	{
		FallingPiece.PositionX += CanPlacePiece(FallingPiece.PositionX + 1, FallingPiece.PositionY, FallingPiece.CurrentRotation);
		bMoveRight = false;
	}
	if (bMoveDown)
	{
		FallingPiece.PositionY -= CanPlacePiece(FallingPiece.PositionX, FallingPiece.PositionY - 1, FallingPiece.CurrentRotation);
	}
	if (bRotate)
	{
		FallingPiece.CurrentRotation += CanPlacePiece(FallingPiece.PositionX, FallingPiece.PositionY, (FallingPiece.CurrentRotation + 1) % 4);
		FallingPiece.CurrentRotation = FallingPiece.CurrentRotation % 4;
		bRotate = false;
	}

	// Process this tick
	CurrentTick++;

	if (CurrentTick == MoveBlockDownTicks)
	{
		CurrentTick = 0;

		if (CanPlacePiece(FallingPiece.PositionX, FallingPiece.PositionY - 1, FallingPiece.CurrentRotation))
		{
			// Yep, it can fall down
			--FallingPiece.PositionY;
		}
		else
		{
			// Falling piece reach a position where it cannot move down anymore
			// Fix it to the board, check for lines, update score and spawn a new piece
			PlacePiece();

			CheckForLineFill();

			UpdateScore();

			SetupNewPiece();

			// Dont update the board here and exit this tick immediately
			// otherwise the new piece will be visualized in this tick even if technically
			// we just set it up in this tick
			return;
		}
	}

	// Update board
	UpdateBoard();
}

void ATetrisGameMode::UpdateBoard()
{
	// Update the board state
	for (uint8 y = 0; y < BoardHeight; ++y)
	{
		for (uint8 x = 0; x < BoardWidth; ++x)
		{
			uint8 CurrentIdx = y * BoardWidth + x;
			
			ATetrisBlock* BoardBlock = Board[CurrentIdx];
			FColor BoardBlockColor = BoardBlock->GetBlockColor();
			FColor CurrentBlockColor = DecodeBlockColor(InternalBoard[CurrentIdx]);			
			
			if (BoardBlockColor != CurrentBlockColor)
			{
				BoardBlock->SetBlockColor(CurrentBlockColor);
			}
		}
	}

	// Update the falling piece
	for (int32 PosY = 0; PosY < 4; ++PosY)
	{
		for (int32 PosX = 0; PosX < 4; ++PosX)
		{
			uint8 LocalPieceIndex = GetIndexBasedOnRotation(PosX, PosY, FallingPiece.CurrentRotation);

			if (TetrisPieces[FallingPiece.CurrentColor - 2].Matrix[LocalPieceIndex] != 0)
			{
				// Current index is a part of the tetris piece
				int32 BoardCoordsX = FallingPiece.PositionX + PosX;
				int32 BoardCoordsY = FallingPiece.PositionY + PosY;

				int32 BoardIndex = BoardCoordsY * BoardWidth + BoardCoordsX;

				// Check if it is within the board limits
				if (BoardCoordsX > 0 ||
					BoardCoordsX < BoardWidth - 1 ||
					BoardCoordsY > 0 ||
					BoardCoordsY < BoardHeight - 1
					)
				{
					Board[BoardIndex]->SetBlockColor(DecodeBlockColor(FallingPiece.CurrentColor));
				}
			}
		}
	}
}

void ATetrisGameMode::CheckForLineFill()
{
	// Scan the board bottom to top...
	for (int32 PosY = 1; PosY < BoardHeight - 1; ++PosY)
	{
		bool bLine = true;
		
		// ... from left to right, without border blocks ....
		for (int32 PosX = 1; PosX < BoardWidth - 1; ++PosX)
		{
			// ... and if there isn't block on the current position, immediately go for the line above
			if (InternalBoard[PosY * BoardWidth + PosX] == 0)
			{
				bLine = false;
				break;
			}
		}				

		// If we got here with bLine = true, then the line was full of blocks
		if (bLine)
		{
			// ... so store the current height (Y line coordinate) where the board is full
			FilledLines.Push(PosY);
		}
	}

	// If any lines should be cleared ...
	if (FilledLines.Num() > 0)
	{
		// ... go through them
		for (uint8 i = 0; i < FilledLines.Num(); ++i)
		{
			uint8 LineY = FilledLines[i];

			// Now start on the x axis, ...
			for (int32 PosX = 1; PosX < BoardWidth - 1; ++PosX)
			{
				// ... iterate up ...
				for (int32 PosY = LineY; PosY < BoardHeight - 1; ++PosY)
				{
					// ... and move each block down
					InternalBoard[PosY * BoardWidth + PosX] = InternalBoard[(PosY + 1) * BoardWidth + PosX];
				}
			}

			// Line was now cleared. But if there were any more to be cleared...
			if (i < FilledLines.Num() - 1)
			{
				// ... we need to go through them ...
				for (uint8 j = i; j < FilledLines.Num(); ++j)
				{
					// ... and lower their Y coordinate, because those were pushed one down
					--FilledLines[j];
				}
			}
		}
	}		
}

void ATetrisGameMode::PlacePiece()
{
	// For each piece coordinate try to place it into the internal board
	for (int32 PosY = 0; PosY < 4; ++PosY)
	{
		for (int32 PosX = 0; PosX < 4; ++PosX)
		{
			uint8 LocalPieceIndex = GetIndexBasedOnRotation(PosX, PosY, FallingPiece.CurrentRotation);

			if (TetrisPieces[FallingPiece.CurrentColor - 2].Matrix[LocalPieceIndex] != 0)
			{
				// Current index is a part of the tetris piece
				int32 BoardCoordsX = FallingPiece.PositionX + PosX;
				int32 BoardCoordsY = FallingPiece.PositionY + PosY;

				int32 BoardIndex = BoardCoordsY * BoardWidth + BoardCoordsX;

				// Check if it is within the board limits
				if (BoardCoordsX > 0 ||
					BoardCoordsX < BoardWidth - 1 ||
					BoardCoordsY > 0 ||
					BoardCoordsY < BoardHeight - 1
					)
				{
					InternalBoard[BoardIndex] = FallingPiece.CurrentColor;
				}
			}
		}
	}
}

void ATetrisGameMode::SetupNewPiece()
{
	FallingPiece.CurrentColor = FMath::RandRange(0, TetrisPieces.Num() - 1) + 2;	// Random tetris piece (2-8 are legal colors)
	FallingPiece.CurrentRotation = 2;					// 180 deg because pieces are in the matrix top->bottom and board is bottom->top
	FallingPiece.PositionX = BoardWidth / 2 - 2;		// In the middle if possible (a half, without border blocks)
	FallingPiece.PositionY = BoardHeight - 4;			// Offset the top by tetris piece height (4x4)

	if (!CanPlacePiece(FallingPiece.PositionX, FallingPiece.PositionY, FallingPiece.CurrentRotation))
	{
		// Game over, cannot place a new piece
		GetWorldTimerManager().ClearTimer(GameTickTimerHandle);
		GameTickTimerHandle.Invalidate();
		UE_LOG(LogTemp, Error, TEXT("GameOver! Score: %d"), Score);
	}
}

void ATetrisGameMode::UpdateScore()
{
	PlacedBlocks++;

	Score += 10;

	if (!FilledLines.IsEmpty())
	{
		// Just a random computation
		Score += (FilledLines.Num() * 2) * 100;

		// Clean up filled lines, the board was updated already
		FilledLines.Empty();
	}

	if (PlacedBlocks % 15 == 0)
	{
		// Increase tick speed of the falling block
		--MoveBlockDownTicks;
		UE_LOG(LogTemp, Warning, TEXT("GETTING FASTER!"));
	}
}

void ATetrisGameMode::ProcessPlayerInput(EInputActionTypes InputType)
{
	switch (InputType)
	{
	case EInputActionTypes::MoveBlockLeft:
		bMoveLeft = true;
		break;

	case EInputActionTypes::MoveBlockRight:
		bMoveRight = true;
		break;

	case EInputActionTypes::MoveBlockDown:
		bMoveDown = true;
		break;

	case EInputActionTypes::RotateBlock:
		bRotate = true;
		break;

	default: // EInputActionTypes::Undefined
		bMoveLeft = false;
		bMoveRight = false;
		bMoveDown = false;
	}
}

FColor ATetrisGameMode::DecodeBlockColor(uint8 TetrisBlockType)
{
	FColor RetColor = FColor::White;
	
	switch (TetrisBlockType)
	{
	case 0: RetColor = FColor::Black; break;
	case 1: RetColor = FColor::White; break;
	case 2: RetColor = FColor::Cyan; break;
	case 3: RetColor = FColor::Yellow; break;
	case 4: RetColor = FColor::Purple; break;
	case 5: RetColor = FColor::Blue; break;
	case 6: RetColor = FColor::Orange; break;
	case 7: RetColor = FColor::Emerald; break;
	case 8: RetColor = FColor::Red; break;
	}

	return RetColor;
}

uint8 ATetrisGameMode::CanPlacePiece(int32 PieceX, int32 PieceY, uint8 PieceRotation)
{
	// For each block in the piece matrix try to find out of it is within board bounds
	// We return 1 even if a part of the piece's matrix does not fit the board!
	// This is OK as long as we care about the occupied block pieces and not empty spaces in the matrix
	for (int32 PosY = 0; PosY < 4; ++PosY)
	{
		for (int32 PosX = 0; PosX < 4; ++PosX)
		{
			uint8 LocalPieceIndex = GetIndexBasedOnRotation(PosX, PosY, PieceRotation);

			int32 BoardCoordsX = PieceX + PosX;
			int32 BoardCoordsY = PieceY + PosY;

			int32 BoardIndex = BoardCoordsY * BoardWidth + BoardCoordsX;

			// Check if we are within bounds
			if (BoardCoordsX > 0 ||
				BoardCoordsX < BoardWidth - 1 ||
				BoardCoordsY > 0 ||
				BoardCoordsY < BoardHeight - 1
				)
			{
				// We are within board bounds for this piece's block
				// Now check if the tested piece block is occupied and the board is occupied
				// if yes, then the Falling Piece cannot be placed at this location
				if (TetrisPieces[FallingPiece.CurrentColor - 2].Matrix[LocalPieceIndex] != 0 && InternalBoard[BoardIndex] != 0)
				{
					return 0;
				}
			}			
		}
	}	
	return 1;
}

uint8 ATetrisGameMode::GetIndexBasedOnRotation(uint8 PosX, uint8 PosY, uint8 CurrentRotation)
{
	uint8 LocalIndex = 0;

	switch (CurrentRotation)
	{
	case 0: LocalIndex = PosY * 4 + PosX; break;
	case 1: LocalIndex = 12 + PosY - (PosX * 4); break;
	case 2: LocalIndex = 15 - (PosY * 4) - PosX; break;
	case 3: LocalIndex = 3 - PosY + (PosX * 4); break;
	}

	return LocalIndex;
}