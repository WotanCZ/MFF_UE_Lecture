// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	check(BlockClassToSpawn);

	const uint32 BoardWidth = 16U;
	const uint32 BoardHeight = 20U;
	const uint32 BlockSize = 100U;

	Board.Reserve(BoardWidth * BoardHeight);

	for (uint32 y = 0; y < BoardHeight; ++y)
	{
		for (uint32 x = 0; x < BoardWidth; ++x)
		{
			const FVector Location(x * BlockSize, 0, y * BlockSize);
			ATetrisBlock* SpawnedBlock = GetWorld()->SpawnActor<ATetrisBlock>(
				BlockClassToSpawn, Location, FRotator::ZeroRotator
			);
			const bool bBorder = x == 0 || x == BoardWidth - 1 || y == 0;
			SpawnedBlock->SetBlockColor(bBorder ? FColor::White : FColor::Black);
			Board.Emplace(SpawnedBlock);
		}
	}
}
