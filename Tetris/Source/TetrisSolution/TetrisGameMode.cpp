// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

void ATetrisGameMode::StartPlay()
{
	Super::StartPlay();



	// init game data
	/*FFallingBlock b;
	b.bInitialized = false;
	b.BlockColor = FLinearColor::Red;
	b.
	TetrisBlocks.Add(
	
	);*/

	// init game from the begining
	RestartGame();
}

void ATetrisGameMode::RestartGame()
{
	// Init board and spawn instanced actors
	Board.Reserve(BoardWidth * BoardHeight);

	uint8 BlockSize = 100;

	UWorld* World = GetWorld();
	check(World);

	for (uint8 i = 0; i < BoardHeight; ++i)
	{
		for (uint8 j = 0; j < BoardWidth; ++j)
		{
			FVector Location = FVector(j * BlockSize, 0, i * BlockSize);
			ATetrisBlock* Block = World->SpawnActor<ATetrisBlock>(BlockClassToSpawn, Location, FRotator::ZeroRotator);
			Board.Emplace(Block);
		}
	}

	ATetrisBlock* Floor = World->SpawnActor<ATetrisBlock>(BlockClassToSpawn, FVector(450, 0, -BlockSize), FRotator::ZeroRotator);
	Floor->SetActorScale3D(FVector(50, 50, 1));
	Floor->SetBlockColor(FLinearColor::White);

	//ATetrisBlock* Floora = World->SpawnActor<ATetrisBlock>(ATetrisBlock::StaticClass(), FVector(500, 0, -BlockSize), FRotator::ZeroRotator);
	//Floor->SetActorScale3D(FVector(50, 50, 1));
	//Floor->SetBlockColor(FLinearColor::White);

	// Clear score
	Score = 0;

	// Set game timer
	World->GetTimerManager().SetTimer(GameTickTimerHandle, this, &ATetrisGameMode::TetrisGameTick, 1.f / TicksPerSecond, true);
}

void ATetrisGameMode::TetrisGameTick()
{
	UE_LOG(LogTemp, Warning, TEXT("TICK"));

	// spawn new block
	if (!CurrentBlock.bInitialized)
	{
		uint8 Min = 0;
		uint8 Max = static_cast<uint8>(EBlockTypes::BlockColorNum);
		uint8 BlockType = FMath::RandRange(Min, Max);

		//CurrentBlock = TetrisBlocks[BlockType];


		//CurrentBlock.bInitialized = true;
	}

	// check if block is placed

	// check after placing for filled line to update board
	CheckForLineFill();

	// update the meshes on the board
	UpdateBoard();
}

void ATetrisGameMode::PutBlockDown()
{
}

void ATetrisGameMode::UpdateBoard()
{
}

void ATetrisGameMode::CheckForLineFill()
{
}
