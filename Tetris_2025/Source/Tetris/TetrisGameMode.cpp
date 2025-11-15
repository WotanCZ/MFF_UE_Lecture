// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

#include "TetrisPlayer.h"
#include "Kismet/GameplayStatics.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	check(BlockClassToSpawn);

	const uint32 BoardWidth = 16u;
	const uint32 BoardHeight = 20u;
	const uint32 BlockSize = 100u;

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

	if (UWorld* World = GetWorld())
	{
		if (ATetrisPlayer* Player = Cast<ATetrisPlayer>(UGameplayStatics::GetPlayerPawn(World, 0)))
		{
			Player->OnGameInputRequested.BindUObject(this, &ATetrisGameMode::ProcessPlayerInput);
		}

		const float TickRate = 1.f / 20;
		World->GetTimerManager().SetTimer(GameTickTimerHandle, this, &ATetrisGameMode::TetrisGameTick,
			TickRate, true
		);
	}
}

void ATetrisGameMode::ProcessPlayerInput(EInputActionType Value)
{
	UE_LOG(LogTemp, Warning, TEXT("ROTATE"));
}

void ATetrisGameMode::TetrisGameTick()
{
	UE_LOG(LogTemp, Warning, TEXT("Tick"));
}
