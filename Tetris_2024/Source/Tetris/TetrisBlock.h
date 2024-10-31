// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlock.generated.h"

UCLASS()
class TETRIS_API ATetrisBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBlock();

	const FColor& GetBlockColor() const;
	void SetBlockColor(const FColor NewColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* BlockMaterialInstance;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicBlockMaterialInstance;
	
	UPROPERTY()
	FColor BlockColor;
	
	UPROPERTY(EditAnywhere)
	FName ColorParameterName;
};
