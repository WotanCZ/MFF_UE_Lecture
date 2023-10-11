// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"


// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create cube component
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));	
	MeshComponent->SetStaticMesh(CubeMesh);	
	MeshComponent->SetWorldScale3D(FVector(0.9f));

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

void ATetrisBlock::SetBlockScale(const float NewScale)
{
	MeshComponent->SetWorldScale3D(FVector(NewScale));
}

const FLinearColor& ATetrisBlock::GetBlockColor() const
{
	return CurrentColor;
}

void ATetrisBlock::SetBlockColor(const FLinearColor& NewColor)
{
	CurrentColor = NewColor;

	if (NewColor == FLinearColor::Black)
	{
		this->SetActorHiddenInGame(true);
	}
	else
	{
		this->SetActorHiddenInGame(false);
		MyDynamicMaterial->SetVectorParameterValue(ColorParameterName, CurrentColor);
	}	
}
