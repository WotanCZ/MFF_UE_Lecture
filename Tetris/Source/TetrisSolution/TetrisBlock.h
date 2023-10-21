// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Include
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// This Include
#include "TetrisBlock.generated.h"


UCLASS()
class TETRISSOLUTION_API ATetrisBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	/** Returns current block's color */
	UFUNCTION(BlueprintCallable)
	const FColor& GetBlockColor() const;

	/** Sets new block color */
	UFUNCTION(BlueprintCallable)
	void SetBlockColor(const FColor& NewColor);

private:
	/** The material of the block */
	UPROPERTY(EditAnywhere)
	UMaterialInstance* MaterialInstance;

	/** The Dynamic instance of the material */
	UPROPERTY()
	UMaterialInstanceDynamic* MyDynamicMaterial;

	/** The color parameter name in the dynamic material - used to change the color of the block */
	UPROPERTY(EditAnywhere)
	FName ColorParameterName = "BlockColor";

	/** The mesh component of this block */
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;

	/** The block's color */
	UPROPERTY()
	FColor CurrentColor = FColor::Black;	
};
