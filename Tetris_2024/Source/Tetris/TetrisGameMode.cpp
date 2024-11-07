// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "TetrisPlayer.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (ATetrisPlayer* Pawn = Cast<ATetrisPlayer>(UGameplayStatics::GetPlayerPawn(World, 0)))
		{
			Pawn->OnGameInputRequested.BindUObject(this,
				&ATetrisGameMode::ProcessPlayerInput);
		}

		check(BlockClassToSpawn);

		int32 BlockSize = 100;

		Board.Init(nullptr, BoardWidth * BoardHeight);

		for (auto y = 0; y < BoardHeight; ++y)
		{
			for (auto x = 0; x < BoardWidth; ++x)
			{
				int32 CurrentIdx = y * BoardWidth + x;

				FVector Location = FVector(x*BlockSize, 0, y*BlockSize);

				Board[CurrentIdx] = World->SpawnActor<ATetrisBlock>(
					BlockClassToSpawn, Location, FRotator::ZeroRotator
				);

				bool bisBorder = (x == 0 || x == BoardWidth-1 || y == 0);

				Board[CurrentIdx]->SetBlockColor(bisBorder ? 
					FColor::White :
					FColor::Black
				);
			}
		}

		ATetrisBlock* Floor = World->SpawnActor<ATetrisBlock>(
			BlockClassToSpawn, FVector(450,0, -BlockSize), FRotator::ZeroRotator
		);
		Floor->SetActorScale3D(FVector(50,50,1));
		Floor->SetBlockColor(FColor::Green);

		World->GetTimerManager().SetTimer(
			GameTickHandle, this, &ATetrisGameMode::TetrisGameTick,
			1.f / TicksPerSecond, true
		);
	}
}

void ATetrisGameMode::ProcessPlayerInput(EInputActionTypes Value)
{
	switch (Value)
	{
	case EInputActionTypes::MoveBlockLeft:
		UE_LOG(LogTemp, Warning, TEXT("Left"));
		break;
	case EInputActionTypes::MoveBlockRight:
		UE_LOG(LogTemp, Warning, TEXT("Right"));
		break;
	case EInputActionTypes::PlaceBlock:
		UE_LOG(LogTemp, Warning, TEXT("Place"));
		break;
	case EInputActionTypes::RotateBlock:
		UE_LOG(LogTemp, Warning, TEXT("Rotate"));
		break;
	default: // EInputActionTypes::Undefined
		UE_LOG(LogTemp, Warning, TEXT("Release"));
		break;
	}
}

void ATetrisGameMode::TetrisGameTick()
{
	UE_LOG(LogTemp, Warning, TEXT("TICK"));
}
