// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"

// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	MeshComponent->SetStaticMesh(CubeMesh);
	MeshComponent->SetWorldScale3D(FVector(0.9f));

	RootComponent = MeshComponent;
}

const FColor& ATetrisBlock::GetBlockColor() const
{
	return BlockColor;
}

void ATetrisBlock::SetBlockColor(const FColor NewColor)
{
	BlockColor = NewColor;

	if (BlockColor == FColor::Black)
	{
		this->SetActorHiddenInGame(true);
	}
	else
	{
		DynamicBlockMaterialInstance->SetVectorParameterValue(ColorParameterName, BlockColor);
		this->SetActorHiddenInGame(false);
	}
}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BlockMaterialInstance))
	{
		DynamicBlockMaterialInstance = UMaterialInstanceDynamic::Create(BlockMaterialInstance, this);
		MeshComponent->SetMaterial(0, DynamicBlockMaterialInstance);
		SetBlockColor(FColor::Blue);
	}	
}

// Called every frame
void ATetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

