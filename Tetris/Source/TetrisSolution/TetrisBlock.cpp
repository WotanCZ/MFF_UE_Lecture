// Fill out your copyright notice in the Description page of Project Settings.

// This Include
#include "TetrisBlock.h"


// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create cube Mesh
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	
	// Create mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));	
	MeshComponent->SetStaticMesh(CubeMesh);	
	MeshComponent->SetWorldScale3D(FVector(0.9f));

	// Set it as a root component
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(MaterialInstance))
	{
		MyDynamicMaterial = UMaterialInstanceDynamic::Create(MaterialInstance, this);
		MeshComponent->SetMaterial(0, MyDynamicMaterial);
		MyDynamicMaterial->SetVectorParameterValue(ColorParameterName, CurrentColor);
	}
	this->SetActorHiddenInGame(true);
}

const FColor& ATetrisBlock::GetBlockColor() const
{
	return CurrentColor;
}

void ATetrisBlock::SetBlockColor(const FColor& NewColor)
{
	CurrentColor = NewColor;

	if (NewColor == FColor::Black)
	{
		this->SetActorHiddenInGame(true);
	}
	else
	{
		this->SetActorHiddenInGame(false);
		MyDynamicMaterial->SetVectorParameterValue(ColorParameterName, CurrentColor);
	}
}