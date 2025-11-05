// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"

// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
		TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	MeshComponent->SetStaticMesh(CubeMesh);
	MeshComponent->SetWorldScale3D(FVector(0.9f));
}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();

	check(BlockMaterialInstance);

	//if (IsValid(BlockMaterialInstance))
	{
		BlockMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(BlockMaterialInstance, this);
		MeshComponent->SetMaterial(0, BlockMaterialInstanceDynamic);
	}

	uint8 R = static_cast<uint8>(FMath::SRand() * 255);
	uint8 G = static_cast<uint8>(FMath::SRand() * 255);
	uint8 B = static_cast<uint8>(FMath::SRand() * 255);

	SetBlockColor(FColor(R, G, B));
}

// Called every frame
void ATetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const FColor ATetrisBlock::GetBlockColor()
{
	return BlockColor;
}

void ATetrisBlock::SetBlockColor(const FColor NewColor)
{
	BlockColor = NewColor;

	if (BlockColor == FColor::Black)
	{
		SetActorHiddenInGame(true);
	}
	else
	{
		SetActorHiddenInGame(false);
		BlockMaterialInstanceDynamic->SetVectorParameterValue(BlockParameterName, BlockColor);
	}
}

